# Overview

MicroEJ Testsuite for "External Resources Loader" Foundation Library.

## Prerequisites

This testsuite requires the FS API version `2.0.6`.


In order to make this testsuite compliant with all implementations of external resource loader, an interface named `ExternalResourceWriter` has been designed. This interface allows to define a resource writer according the external resource implementation used. For example, if the file system is used, API related to the file system are used to develop a new class that `implements` the interface `ExternalResourceWriter`. This testsuite provides by default the file system implementation with the class `FileResourceWriter`.

Consequently, the testsuite requires you to set the property `com.microej.extres.test.utility.resourcewriter` according your implementation of the interface `ExternalResourceWriter`. For example, if your implementation is based on the file system, your can use the class `FileResourceWriter` so the property should be set as follows: `com.microej.extres.test.utility.resourcewriter=com.microej.extres.test.utility.FileResourceWriter`

If you want to try some tests with the simulator, please set the property `ej.externalResources.input.dir=` to `${project_loc:external-resource-testsuite}/src/test/resources` in your application launcher (Run Configuration > Configuration Tab > External Resources Loader).

If your implementation has not an available implementation of `ExternalResourceWriter`, please create it and update this testsuite with this additional support.


Below is the Javadoc of the interface `ExternalResourceWriter` with its methods to override.

### `public interface ExternalResourceWriter`

Interface that allows the external Test Suite to create required external resources according its implementation. Since it is possible to implement external resource loader in many ways, this interface is required for a generic set of tests.

The Test Suite provides a default implementation of this interface with the class FileResourceWriter. This class can be used if the external resource implementation is based on a file system.

If your implementation of the external resource does not have its implementation of the interface ExternalResourceWriter, please update this Test Suite with the required implementation of this interface.

### `OutputStream setResourceAsStream(String name) throws IOException`

Retrieves the OutputStream of the resource converted from the external resource implementation. The user should be able to read and write with this OutputStream.

 * **Parameters:** `name` — The name of the resource with its complete path.

 * **Returns:** The OutputStream opened of the resource targeted by the parameter name.

 * **Exceptions:** `IOException` — If an issue occurred with the targeted resource i.e. wrong name.

### `void clearResource(String name)`

Removes the resource with the given name.

 * **Parameters:** `name` — The name of the resource with its complete path.

### `long getFreeSpace()`

Indicates the remaining space in bytes in the external resource domain.

 * **Returns:** The remaining space in bytes in the external resource domain.


## Tests specification

The class `TestExternalResource` holds common tests for all External Resource Loader implementations, below are details of each tests.

### `@Test  public static void openInvalidPath()`
Checks that an exception is thrown when an invalid path is used with Open method.

### `@Test  public static void openValidPath()`
Opens an inputstream of a valid external resource and expects a non-null result.

### `@Test  public static void closeValidInputStream()`
Checks that the resource is closed correctly in a valid use case.

### `@Test  public static void availableValidInputStream()`
Performs the method available in a valid use case and checks the result.

### `@Test  public static void availableEndOfFile()`
Uses the method available after reading all data of a resource, expected result is 0.

### `@Test  public static void readEndOfFile()`
Reads until we get the information that we reach the end of resource.

### `@Test  public static void readValidPartialBuffer()`
Performs a read with a buffer higher than the amount of data to read. Expects to have all data in buffers.

### `@Test  public static void readTooMuchBytes()`
Performs a read with a value higher than the amount of data in the resource, expects the right amount of data read, not more.

### `@Test  public static void readMoreThanBuffer() throws IOException`
Performs a read with a value higher than the amount of data that can store the input buffer, to get an IndexOutOfBoundsException.

 * **Exceptions:** `IOException` — Thrown if call of read fails, which is expected.

### `@Test  public static void readNegativeLength() throws IOException`
Performs a read with a negative offset in parameter in order to get an IndexOutOfBoundsException.

 * **Exceptions:** `IOException` — Thrown if call of read fails, which is expected.

### `@Test  public static void readNegativeOffset() throws IOException`
Performs a read with a negative offset in parameter in order to expect an IndexOutOfBoundsException.

 * **Exceptions:** `IOException` — Thrown if call of read fails, which is expected.


### `@Test  public static void skipNegative()`
Attempts to do a skip with a negative value in parameter, expects a skip of 0.

### `@Test  public static void skipMoreThanFile()`
Performs a skip with a value in parameter that exceeds the amount of data in the resource. Checks that the returned value by skip is equal to the amount of bytes in the resource, not more.

### `@Test  public static void skipValid()`
Reads an external source and skip one byte on two. Then, check if values read are correct considering the skip done each time.


### `@Test  public static void resetNoMark()`
Checks that an IO exception is thrown when call of reset is done without first call of method.

### `@Test  public static void markAndResetValid()`
Checks that the use of methods Mark and Reset works correctly in a valid use case.

###	 `@Test	public static void callMethodsStreamClosed()`
Checks that the call of InputStream methods throw an exception when the InputStream is closed.

The class `TestBenchmarkReadExternalResource` performs benchmark tests to compute the read speed of the external resource implementation.

### `@Test  public static void run() throws IOException`

Run the read benchmark to compute the read speed of an external resource.

 * **Exceptions:** `IOException` — If there was an error reading data.


### Scope limitation of tests

The current version of the testsuite has no tests to check specificities of byte-addressable resources.

# Usage

Add the following line to your `module.ivy`:

    @MMM_DEPENDENCY_DECLARATION@

# Requirements

This library requires the following Foundation Libraries:

    @FOUNDATION_LIBRARIES_LIST@

# Dependencies

_All dependencies are retrieved transitively by MicroEJ Module Manager_.

# Source

N/A.

# Restrictions

None.

---

Copyright 2023 MicroEJ Corp. All rights reserved.
Use of this source code is governed by a BSD-style license that can be found with this software.