/*
 * Java
 *
 * Copyright 2021 MicroEJ Corp. All rights reserved.
 * This library is provided in source code for use, modification and test, subject to license terms.
 * Any modification of the source code will break MicroEJ Corp. warranties on the whole library.
 */
package com.microej.ui.tests;

import static org.junit.Assert.assertEquals;

import org.junit.BeforeClass;
import org.junit.Test;

import ej.bon.Util;
import ej.microui.MicroUI;
import ej.microui.display.Colors;
import ej.microui.display.Display;
import ej.microui.display.GraphicsContext;
import ej.microui.display.Painter;

/**
 * MicroEJ UI Validation tests.
 */
public class MicroejUiValidation {

	private static final String VERSION = "1.0.0";

	/**
	 * Properties suffix: add "-Dcom.microej.ui.tests.xxx=xxx" in your JRE tab
	 */
	private static final String PROPERTY_SUFFIX = "com.microej.ui.tests.";

	/**
	 * Property to fix each test time; default value is 10s.
	 */
	private static final String OPTION_CLOCK_NB_SECONDS = "clock.seconds";
	private static final int DEFAULT_TIME_TEST_SECONDS = 10;

	/**
	 * Property to fix the flush time tolerance. This value must be lower than hardware flush time.
	 */
	private static final String OPTION_FLUSH_TOLERANCE_NB_US = "flush.tolerance.us";
	private static final int DEFAULT_TIME_TOLERANCE_US = 200;

	private static void printProduct() {
		final String sep = "*****************************************************************************************************";
		System.out.println(sep);
		System.out.println("*                                  MicroEJ UI Validation - " + VERSION
				+ "                                  *");
		System.out.println(sep);
		System.out.println(
				"* Copyright 2021 MicroEJ Corp. All rights reserved.                                                 *");
		System.out.println(
				"* This library is provided in source code for use, modification and test, subject to license terms. *");
		System.out.println(
				"* Any modification of the source code will break MicroEJ Corp. warranties on the whole library.     *");
		System.out.println(sep);
		System.out.println();
	}

	private static int getOptionAsInt(String optionName, int defaultValue, String unit) {
		String propertyName = PROPERTY_SUFFIX + optionName;
		String valueStr = System.getProperty(propertyName);
		int value;
		if (valueStr == null) {
			value = defaultValue;
			System.out.println("Property '" + propertyName + "' is not set (default to '" + value + "' " + unit + ")");
		} else {
			try {
				value = Integer.parseInt(valueStr);
				System.out.println("Property '" + propertyName + "' is set to '" + value + "' " + unit);
			} catch (NumberFormatException e) {
				value = defaultValue;
				System.out.println("Property '" + propertyName + "' is invalid (set to '" + valueStr + "', default to '"
						+ value + "' " + unit + ")");
			}
		}
		return value;
	}

	/**
	 * @throws java.lang.Exception
	 *             If an error occurred.
	 */
	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
		MicroUI.start();
		printProduct();
	}

	/**
	 * Tests the <code>LLUI_DISPLAY_IMPL_flush</code> implementation: the LCD tearing (flickering).
	 * <p>
	 * Shows alternately black and white screens. The tearing effect is visible when the screen is cut in two or more
	 * parts.
	 */
	@Test
	public void testTearingFullScreen() {
		System.out.println("-> Check LCD tearing: full screen (LLUI_DISPLAY_IMPL_flush validation)...");
		int nbSeconds = getOptionAsInt(OPTION_CLOCK_NB_SECONDS, DEFAULT_TIME_TEST_SECONDS, "second(s)");

		Display display = Display.getDisplay();
		GraphicsContext gc = display.getGraphicsContext();

		// Check if a message is printed every seconds in terminal:
		long timeStart = System.currentTimeMillis();
		long nbMilliSeconds = nbSeconds * 1000;
		while (true) {
			gc.setColor(Colors.WHITE);
			Painter.fillRectangle(gc, 0, 0, display.getWidth(), display.getHeight());
			display.flush();
			gc.setColor(Colors.BLACK);
			Painter.fillRectangle(gc, 0, 0, display.getWidth(), display.getHeight());
			display.flush();
			long time = System.currentTimeMillis();
			long delta = time - timeStart;
			if (delta > nbMilliSeconds) {
				break; // end of test
			}
		}
	}

	/**
	 * Tests the <code>LLUI_DISPLAY_IMPL_flush</code> implementation: the LCD tearing (flickering).
	 * <p>
	 * Shows a vertical black band that moves as fast as possible on a white background. The tearing effect is visible
	 * when the vertical band is cut in two or more parts.
	 */
	@Test
	public void testTearingVerticalBand() {
		System.out.println("-> Check LCD tearing: black band (LLUI_DISPLAY_IMPL_flush validation)...");

		Display display = Display.getDisplay();
		GraphicsContext g = display.getGraphicsContext();
		int displayWidth = display.getWidth();
		int displayHeight = display.getHeight();

		// retrieve test time
		int nbSeconds = getOptionAsInt(OPTION_CLOCK_NB_SECONDS, DEFAULT_TIME_TEST_SECONDS, "second(s)");

		long timeStart = System.currentTimeMillis();
		long nbMilliSeconds = nbSeconds * 1000;
		int bandWidth = displayWidth / 10;
		int bandX = 0;
		int bandXIncrement = 4;

		do {

			// draw background
			g.setColor(Colors.WHITE);
			Painter.fillRectangle(g, 0, 0, displayWidth, displayHeight);

			// draw band
			g.setColor(Colors.BLACK);
			Painter.fillRectangle(g, bandX, 0, bandWidth, displayHeight);

			// flush content
			display.flush();

			// get next band position
			bandX += bandXIncrement;
			if (bandX + bandWidth >= displayWidth || bandX <= 0) {
				bandXIncrement = -bandXIncrement;
			}

		} while (System.currentTimeMillis() - timeStart < nbMilliSeconds);
	}

	/**
	 * Called by {@link #testDrawingTime()} to force a flush and wait the end of this flush.
	 */
	private void forceFlushAndWait() {
		Display display = Display.getDisplay();
		GraphicsContext gc = display.getGraphicsContext();

		// have to draw something to "enable" the flush
		Painter.writePixel(gc, 0, 0);
		Painter.writePixel(gc, display.getWidth() - 1, display.getHeight() - 1);

		display.flush();
		display.waitFlushCompleted();
	}

	/**
	 * Called by {@link #testDrawingTime()} to get the framerate time according a given drawing time.
	 */
	private int getFramerateTimeUs(int drawingTimeUs) {

		int nbLoops = 20;
		long timeCounter = 0;
		long drawingTimeNs = drawingTimeUs * 1000;

		forceFlushAndWait();

		for (int i = nbLoops; --i >= 0;) {

			long t0 = Util.platformTimeNanos();

			// simulate some drawings
			while (Util.platformTimeNanos() - t0 < drawingTimeNs) {
				;
			}

			forceFlushAndWait();

			long t1 = Util.platformTimeNanos();
			timeCounter += (t1 - t0);
		}
		return (int) (timeCounter / 1000 / nbLoops);
	}

	/**
	 * Called by {@link #testDrawingTime()} to find the maximum drawing time without exceed framerate time.
	 */
	private int adjustDrawingTime(int drawingTimeUs, int drawingTimeStepUs, int framerateTimeRefUs,
			int framerateTimeToleranceUs) {

		int framerateWithDrawingTimeUs = framerateTimeRefUs;
		while (framerateWithDrawingTimeUs < framerateTimeRefUs + framerateTimeToleranceUs) {
			drawingTimeUs += drawingTimeStepUs;
			framerateWithDrawingTimeUs = getFramerateTimeUs(drawingTimeUs);
			// System.out.println(drawingTimeUs + " " + framerateWithDrawingTimeUs);
		}
		return drawingTimeUs - drawingTimeStepUs;
	}

	/**
	 * Called by {@link #testDrawingTime()} to print a report
	 */
	private void printFramerateReport(float frequency, int div, int framerateTimeUs, int flushTimeMs) {
		System.out.print("To have an animation at ");
		System.out.print(frequency / div);
		System.out.print(" Hz, the drawing time cannot be higher than ");
		System.out.print(((float) (framerateTimeUs * div - flushTimeMs)) / 1000);
		System.out.print(" ms.\n");
	}

	/**
	 * Tests the <code>LLUI_DISPLAY_IMPL_flush</code> implementation: the drawing time.
	 * <p>
	 * Determinates the maximum drawing time to have the better framerate as possible.
	 */
	@Test
	public void testDrawingTime() {

		// retrieve flush time tolereance
		int framerateTimeToleranceUs = getOptionAsInt(OPTION_FLUSH_TOLERANCE_NB_US, DEFAULT_TIME_TOLERANCE_US, "us");

		// retrieve LCD framerate time and frequency
		int framerateTimeUs = getFramerateTimeUs(0);
		float framerateHz = 1000000 / (float) framerateTimeUs;
		System.out.println("LCD framerate time is " + framerateTimeUs + " us (" + framerateHz + " Hz)");

		// retrieve maximum drawing time to have better framerate
		System.out.println("Retrieve the maximal drawing time (this will take several seconds)...");
		int drawingTimeUs = 0;
		for (int drawingTimeStepUs = 1000; drawingTimeStepUs >= 10; drawingTimeStepUs /= 10) {
			drawingTimeUs = adjustDrawingTime(drawingTimeUs, drawingTimeStepUs, framerateTimeUs,
					framerateTimeToleranceUs);
		}

		// retrieve flush time thanks to LCD framerate and maximum drawing time
		int flushTimeUs = framerateTimeUs - drawingTimeUs;

		// print reports
		System.out.println("The flush time is " + flushTimeUs + " us");
		printFramerateReport(framerateHz, 1, framerateTimeUs, flushTimeUs);
		printFramerateReport(framerateHz, 2, framerateTimeUs, flushTimeUs);
		printFramerateReport(framerateHz, 3, framerateTimeUs, flushTimeUs);
	}

	/**
	 * Tests the <code>LLUI_DISPLAY_IMPL_flush</code> implementation: the post-flush copy
	 * <p>
	 * After the flush step, the <code>LLUI_DISPLAY_IMPL_flush</code> implementation has to restore the content of
	 * returned backbuffer with the content of flushed back buffer (MicroUI specification). This prevent to the MicroUI
	 * application to draw again the old content.
	 */
	@Test
	public void testBackBufferRestore() {

		Display display = Display.getDisplay();
		GraphicsContext g = display.getGraphicsContext();
		int displayWidth = display.getWidth();
		int displayHeight = display.getHeight();

		// draw in all back buffer and flush it
		g.setColor(Colors.WHITE);
		Painter.fillRectangle(g, 0, 0, displayWidth, displayHeight);
		display.flush();

		// draw in all back buffer and flush it
		g.setColor(Colors.BLACK);
		Painter.fillRectangle(g, 0, 0, displayWidth, displayHeight);
		display.flush();

		// here: the copy after a flush has to restore the content of
		// flushed backbuffer: a black rectangle. If the color is not black,
		// it means the post copy has not been performed or not fully done.

		assertEquals("[A] testBackBufferRestore at 0,0", display.getDisplayColor(Colors.BLACK),
				g.readPixel(0, 0) & 0xffffff);
		assertEquals("[A] testBackBufferRestore at w-1,0", display.getDisplayColor(Colors.BLACK),
				g.readPixel(displayWidth - 1, 0) & 0xffffff);
		assertEquals("[A] testBackBufferRestore at 0,h-1", display.getDisplayColor(Colors.BLACK),
				g.readPixel(0, displayHeight - 1) & 0xffffff);
		assertEquals("[A] testBackBufferRestore at w-1,h-1", display.getDisplayColor(Colors.BLACK),
				g.readPixel(displayWidth - 1, displayHeight - 1) & 0xffffff);

		// draw in all back buffer and flush it
		g.setColor(Colors.WHITE);
		Painter.fillRectangle(g, 0, 0, displayWidth, displayHeight);
		display.flush();

		// draw in the middle of back buffer and flush it
		int offset = 10;
		g.setColor(Colors.BLACK);
		g.setClip(offset, offset, displayWidth - 2 * offset, displayHeight - 2 * offset);
		Painter.fillRectangle(g, 0, 0, displayWidth, displayHeight);
		display.flush();

		// here: the copy after a flush has to restore the content of
		// flushed backbuffer: a black rectangle in the middle of white background.

		assertEquals("[B] testBackBufferRestore at 0,0", display.getDisplayColor(Colors.WHITE),
				g.readPixel(0, 0) & 0xffffff);
		assertEquals("[B] testBackBufferRestore at w-1,0", display.getDisplayColor(Colors.WHITE),
				g.readPixel(displayWidth - 1, 0) & 0xffffff);
		assertEquals("[B] testBackBufferRestore at 0,h-1", display.getDisplayColor(Colors.WHITE),
				g.readPixel(0, displayHeight - 1) & 0xffffff);
		assertEquals("[B] testBackBufferRestore at w-1,h-1", display.getDisplayColor(Colors.WHITE),
				g.readPixel(displayWidth - 1, displayHeight - 1) & 0xffffff);

		assertEquals("[C] testBackBufferRestore at o,o", display.getDisplayColor(Colors.BLACK),
				g.readPixel(offset, offset) & 0xffffff);
		assertEquals("[C] testBackBufferRestore at w-2*o-1,0", display.getDisplayColor(Colors.BLACK),
				g.readPixel(displayWidth - 2 * offset - 1, offset) & 0xffffff);
		assertEquals("[C] testBackBufferRestore at p,h-2*o-1", display.getDisplayColor(Colors.BLACK),
				g.readPixel(offset, displayHeight - 2 * offset - 1) & 0xffffff);
		assertEquals("[C] testBackBufferRestore at w-2*p-1,h-2*o-1", display.getDisplayColor(Colors.BLACK),
				g.readPixel(displayWidth - 2 * offset - 1, displayHeight - 2 * offset - 1) & 0xffffff);
	}
}
