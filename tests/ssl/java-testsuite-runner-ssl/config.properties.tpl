# Properties
#
# Copyright 2022-2024 MicroEJ Corp. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be found with this software.

###############################################################################
# 						Testsuite Configuration Options
#
# Usage: 
#   Uncomment and set options marked '[required]'. 
#   Other options are set with a value that shall not be changed by default.
# 
# Each option can be declared outside this file as a system property:
# In the SDK, select 'Window' > 'Preferences' > 'Ant' > 'Runtime' > 'Properties'
# This can be useful to avoid to share absolute file-system locations in this file.
# In this case, it overrides the option defined in this file if any.
# Moreover, options related to local setup (absolute file-system locations, trace ip & port)
# can be extracted to the file 'local.properties' which is ignored for source control.   
#
# This file respects the Java properties file convention: the OS path
# must use the UNIX path convention (path separator is '/'). The WINDOWS
# paths must have been converted manually replacing '\' by '/' or by '\\'.
###############################################################################

###############################################################################
# Target VEE Port [required]
###############################################################################

# target.platform.dir=[absolute_path]

###############################################################################
# BSP Connection [required]
# Uncomment one and only one option block depending on how the target VEE Port is connected to BSP.  
# See https://docs.microej.com/en/latest/VEEPortingGuide/platformCreation.html
###############################################################################

# No BSP Connection
#microej.testsuite.properties.deploy.dir.microejapp=[absolute_path]
#microej.testsuite.properties.deploy.dir.microejlib=[absolute_path]
#microej.testsuite.properties.deploy.dir.microejinc=[absolute_path]
#microej.testsuite.properties.deploy.dir.microejscript=[absolute_path]

# Partial BSP Connection
#microej.testsuite.properties.deploy.bsp.root.dir=[absolute_path]
#microej.testsuite.properties.deploy.bsp.microejscript=true

# Full BSP Connection
#microej.testsuite.properties.deploy.bsp.microejscript=true

###############################################################################
# Trace Redirection (System.out)
# [required] when trace is redirected by 'Serial to Socket Transmitter' tool,
# otherwise the trace is assumed to be redirected by 'run.bat' or 'run.sh' script.
###############################################################################

#microej.testsuite.properties.testsuite.trace.ip=localhost
#microej.testsuite.properties.testsuite.trace.port=5555

# VEE Port specific option to redirect trace on dedicated UART
#microej.testsuite.properties.debug.traces.uart=SET

###############################################################################
# Tests to run
###############################################################################

# Comma separated list of patterns of files that must be included	
test.run.includes.pattern=**/Test*.class
# Comma separated list of patterns of files that must be excluded (defaults to inner classes)
# **/TestHandshakePki*.class: PKI tests are used to check certificate chain validation policies.
test.run.excludes.pattern=**/*$*.class, **/TestHandshakePki*.class

#######################################################################
# Advanced Options
# These options shall not be changed by default.
###############################################################################

# The execution target (`MICROJVM` to execute on Device, `S3` to execute on Simulator)
target.vm.name=MICROJVM

# The deploy tool to run after the build of the microejapp.o (defaults to 'Platform Configuration Additions')
microej.testsuite.properties.microejtool.deploy.name=deployToolBSPRun

# Set the verbose or not. Possible values: `true` or `false`
# When this option is set to `true`, the harness will output the execution trace.
microej.testsuite.verbose=true

# The testsuite timeout (in seconds)
microej.testsuite.timeout=600

# The number of times we'll retry a test if it fails
microej.testsuite.retry.count=1

# Retry a test unless this pattern is shown
microej.testsuite.retry.unless=MicroEJ START

# A jvm args to pass to the testsuite harness
microej.testsuite.jvmArgs=-Xmx768m

# A jvm args to pass to launch scripts forked vm
microej.testsuite.properties.launch.properties.jvm=-Xmx2048M

# The foundation jars used for the code coverage, useful only if the target.vm.name = S3
microej.testsuite.cc.jars.name.regex=ssl-(.*)\.jar
