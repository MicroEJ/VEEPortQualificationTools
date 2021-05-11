..
    Copyright 2020-2021 MicroEJ Corp. All rights reserved.
    Use of this source code is governed by a BSD-style license that can be found with this software.
..

*********************
Filesystem Test Suite
*********************

This folder contains a ready-to-use project for testing `File System <https://docs.microej.com/en/latest/PlatformDeveloperGuide/fs.html>`_ implementations on a device.
This test suite will typically test file and directory creation, access permissions, and file content read/write...

Specifications
--------------

- Tested Foundation Library: `FS <https://repository.microej.com/modules/ej/api/fs/>`_
- Test Suite Module: `com.microej.pack.fs#fs-testsuite <https://repository.microej.com/modules/com/microej/pack/fs/fs-testsuite/>`_

Update the FS Test Suite module version in the `module.ivy
<java/java-testsuite-fs/module.ivy>`_ to match the requirement of the platform
tested.

Please refer to `Platform Qualification Test Suite Versioning
<https://docs.microej.com/en/latest/PlatformDeveloperGuide/platformQualification.html#test-suite-versioning>`_
to determine the FS Test Suite module version.

Prerequisites
-------------

Before starting the test suite, make sure you have the following requirements:

- MicroEJ SDK version ``5.1.1`` or higher.
- A MicroEJ Platform imported in the workspace, which has been built using `Platform Configuration Additions <../../framework/platform/README.rst>`_ version ``1.0.0`` or higher.
- A device connected to the PC both for programming and to get output traces. See Platform specific documentation for setup. 
- If the Platform requires output traces redirection (e.g. when your device dumps the standard output on a serial port), start the
  `Serial to Socket Transmitter <https://docs.microej.com/en/latest/ApplicationDeveloperGuide/serialToSocketTransmitter.html>`_ tool.

Test Suite Configuration
------------------------

- In MicroEJ SDK, import the ``java/java-testsuite-fs`` project in your workspace.
- Create the local ``config.properties`` file. The Platform may provide a pre-configured ``config.properties`` file under
  ``[platform]-configuration/testsuites/fs/`` folder. By default, copy the ``config.properties.tpl`` to ``config.properties``.
- Open the ``config.properties`` file.
- Fill the options marked as ``[required]``, particularly:

  - Target Platform: set ``target.platform.dir`` to the absolute path of the Platform being tested (the parent folder of the ``release.properties`` file and the platform sources, see `Setup a Platform for Tests <https://docs.microej.com/en/latest/ApplicationDeveloperGuide/testsuite.html#setup-a-platform-for-tests>`__),
  - `BSP Connection <https://docs.microej.com/en/latest/PlatformDeveloperGuide/platformCreation.html#bsp-connection>`_: check the Platform specific documentation to get the kind of configured BSP connection.
  - Trace Redirection (if the Platform requires output traces redirection): set options in sync with the Serial to Socket Transmitter options.

- Check `Application Options <https://docs.microej.com/en/latest/ApplicationDeveloperGuide/applicationOptions.html>`_ declared in ``validation/microej-testsuite-common.properties``. 
  By default, options are initialized with suitable values to successfully execute the whole test suite and should not be changed. 
  However in some particular cases, you can adjust test suite specific options or memory settings.

Test Suite Execution
--------------------

Right-click on the ``java-testsuite-fs`` project and click on ``Build Module``.

Please refer to `Platform Qualification documentation <https://docs.microej.com/en/latest/PlatformDeveloperGuide/platformQualification.html>`_ to know more about test suites and how to get reports.

Troubleshooting
---------------

No activity on input stream
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following error indicates that no output have been seen by the
Serial To Socket.

- Ensure that the COM port configured for the Serial To Socket is
  correct.
- Check the Platform documentation on how to connect to the UART
  output for the test suites.

.. code-block::

   [testsuite:javaTestsuite] [traceAnalyzer:socketTraceAnalyzer] 1 : TraceAnalyzer ERROR :
   [testsuite:javaTestsuite] [traceAnalyzer:socketTraceAnalyzer] [M3] - No activity on input stream since 75 s.
   [testsuite:javaTestsuite] [traceAnalyzer:socketTraceAnalyzer] 
   [testsuite:javaTestsuite] [traceAnalyzer:socketTraceAnalyzer] 2 : TraceAnalyzer ERROR :
   [testsuite:javaTestsuite] [traceAnalyzer:socketTraceAnalyzer] [M5] - No encountered success/failure tag.
   [testsuite:javaTestsuite] [traceAnalyzer:socketTraceAnalyzer] 
   [testsuite:javaTestsuite] BUILD FAILED
   [testsuite:javaTestsuite] C:\Program Files\MicroEJ\MicroEJ-SDK-20.12\rcp\configuration\org.eclipse.osgi\11\data\repositories\microej-build-repository\com\is2t\easyant\plugins\microej-testsuite\3.4.0\microej-testsuite-harness-jpf-emb-3.4.0.xml:85: TraceAnalyzer ends with errors.

Could not open port 'COMxxx'
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following error indicates that the COM port can not be opened.

- Ensure that the COM port configured for the Serial To Socket is
  correct.
- Only one application may open a given COM port.  Ensure no other
  application are using this COM port.
- COM port may changed when the device is unplugged.  Ensure that the
  COM port configured for the Serial To Socket is correct.

.. code-block::

   serial.serialutil.SerialException: could not open port 'COM7': FileNotFoundError(2, 'The system cannot find the file specified.', None, 2)

No loaded Platform
~~~~~~~~~~~~~~~~~~

.. code-block::

   No loaded Platform.
   Possible options to load a platform are: 
   - (1) Set the property `platform-loader.target.platform.file` to a Platform file absolute path.
   - (2) Set the property `platform-loader.target.platform.dir` to a Platform directory absolute path.
   - (3) Declare a dependency in `module.ivy`.
   - (4) Copy/Paste a Platform file into the folder defined by the property `platform-loader.target.platform.dropins` (by default its value is `dropins`).
   A Platform declared using (1) or (2) is loaded prior to (3) or (4).

Ensure the property ``target.platform.dir`` is set in
``config.properties`` and points to the Platform source folder.

Could not connect to localhost:5555
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block::

   [testsuite:javaTestsuite] [traceAnalyzer:socketTraceAnalyzer] 1 : SocketTraceAnalyzerError ERROR :
   [testsuite:javaTestsuite] [traceAnalyzer:socketTraceAnalyzer] [M1] - Could not connect to localhost:5555
   [testsuite:javaTestsuite] [traceAnalyzer:socketTraceAnalyzer] 
   [testsuite:javaTestsuite] BUILD FAILED

- Ensure the Serial To Socket is started and configured to listen on
  the port 5555.  The host and port properties used by the Test Suite
  Engine are configured in ``config.properties``.

The test suite runs but some tests are failing
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- Ensure the Low Level Implementations tested by the test suite are
  correctly implemented.
- Check your Platform documentation on test suites.  The Platform may
  provide specific ``config.properties`` and
  ``microej-testsuite-common.properties``.
