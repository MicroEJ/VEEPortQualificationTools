#!/bin/bash
#
# BASH
#
# Copyright 2024 MicroEJ Corp. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be found with this software.

# 'set_project_env.sh' implementation for IAR BXARM.

# 'set_project_env' is responsible for
# - checking the availability of required environment variables
# - setting project local variables for 'build.sh'

SCRIPT_PATH=$(dirname "$0")

LOCAL_ENV_SCRIPT="$SCRIPT_PATH/set_local_env.sh"
if [[ -e "$LOCAL_ENV_SCRIPT" ]]; then
    echo "Load $LOCAL_ENV_SCRIPT"
    . "$LOCAL_ENV_SCRIPT"
fi

# Required Environment Variable
# IAR Build Tools installation directory (e.g.: /opt/iarsystems/bxarm)
export IAREW_INSTALLATION_DIR=CHANGEIT

# Set the project variables required by the build script for IAR Embedded Workbench
# IAREW project directory that contains the project file .ewp (e.g.: $(dirname "$0"))
export IAREW_PROJECT_DIR=CHANGEIT
# IAREW project file name without the extension .ewp (e.g.: Project)
export IAREW_PROJECT_NAME=CHANGEIT
# IAREW project configuration (e.g.: Debug or Release)
export IAREW_PROJECT_CONFIGURATION=CHANGEIT
# IAREW project output folder configuration (can be the project configuration or a combination with the project name)
export IAREW_PROJECT_OUTPUT_FOLDER=CHANGEIT
# IAREW out file name  (file name defined in IAR project option without .out)
export IAREW_OUT_FILENAME=CHANGEIT

# Path of the the binary file to flash into the board
export IAREW_PROJECT_EXECUTABLE_FILE="$IAREW_PROJECT_DIR/$IAREW_PROJECT_OUTPUT_FOLDER/Exe/$IAREW_OUT_FILENAME.out"

echo IAREW_INSTALLATION_DIR=$IAREW_INSTALLATION_DIR
echo IAREW_PROJECT_DIR=$IAREW_PROJECT_DIR
echo IAREW_PROJECT_NAME=$IAREW_PROJECT_NAME
echo IAREW_PROJECT_CONFIGURATION=$IAREW_PROJECT_CONFIGURATION
echo IAREW_PROJECT_OUTPUT_FOLDER=$IAREW_PROJECT_OUTPUT_FOLDER

