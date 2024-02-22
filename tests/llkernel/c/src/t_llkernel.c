/*
 * C
 *
 * Copyright 2023 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#include "t_llkernel.h"
#include "../../../../framework/c/embunit/embUnit/embUnit.h"
#include "../../../../framework/c/utils/inc/u_print.h"


// --------------------------------------------------------------------------------
// -                                  Constants                                   -
// --------------------------------------------------------------------------------

/**
 * Returned value when function call has succeeded.
 */
#define LLKERNEL_OK (0)

/**
 * Returned value when function call has failed.
 */
#define LLKERNEL_ERROR (-1)

#define NUMBER_OF_FEATURES  6
#define FEATURE_DATA_BUFFER_SIZE                   0x100     /* 256 bytes */


extern int32_t LLKERNEL_IMPL_allocateFeature__II(int32_t size_ROM, int32_t size_RAM);
extern void *LLKERNEL_IMPL_getFeatureAddressROM__I(int32_t handle);
extern void *LLKERNEL_IMPL_getFeatureAddressRAM__I(int32_t handle);
extern int32_t LLKERNEL_IMPL_copyToROM__LiceTea_lang_Ram_2LiceTea_lang_Ram_2I(void *dest_address_ROM, void *src_address, int32_t size);
extern int32_t LLKERNEL_IMPL_flushCopyToROM(void);
extern int32_t LLKERNEL_IMPL_getAllocatedFeaturesCount(void);
extern int32_t LLKERNEL_IMPL_getFeatureHandle__I(int32_t index);
extern void LLKERNEL_IMPL_freeFeature__I(int32_t handle);

static int32_t featureHandles[NUMBER_OF_FEATURES] = {0};

/* @brief Buffer used to store feature data content */
static uint8_t featureDataBuffer[FEATURE_DATA_BUFFER_SIZE] = {0};

static void cleanup_installed_features() {
	// Free installed features
	int32_t nbAllocatedFeatures = LLKERNEL_IMPL_getAllocatedFeaturesCount();
    while(nbAllocatedFeatures > 0){
		int32_t handle = LLKERNEL_IMPL_getFeatureHandle__I(0);
		// Installed feature found, free it
		LLKERNEL_IMPL_freeFeature__I(handle);
		nbAllocatedFeatures = LLKERNEL_IMPL_getAllocatedFeaturesCount();
    }

	// Reset features handle
	for(int32_t i = 0; i < NUMBER_OF_FEATURES; i++) {
		// Deinit associated feature handle
		featureHandles[i] = 0;
	}
}

/** @brief Function call before running test. */
static void T_LLKERNEL_setUp(void)
{
	UTIL_print_string("\nT_LLKERNEL_setUp\n");
	cleanup_installed_features();
	// featureDataBuffer zero init
	memset(featureDataBuffer, 0, FEATURE_DATA_BUFFER_SIZE);
}

/** @brief Function call before running test. */
static void T_LLKERNEL_tearDown(void)
{
	UTIL_print_string("T_LLKERNEL_tearDown\n");
	cleanup_installed_features();
}

/** @brief 	Allocate and install max number of features.
 * 		Test should fail after installing the max number of features (max number depending on the implementation).
 */
static void T_LLKERNEL_CHECK_resource_allocate(void) {
	UTIL_print_string("LLKERNEL resource allocate\n");
        
    uint8_t tmpBuffer[FEATURE_DATA_BUFFER_SIZE] = {0};
    int32_t installed_features = 0;
    int32_t featureHandle = 0;

    do {
        sprintf((char*)featureDataBuffer, "********llkernel %d llkernel*******", installed_features);

        // Save content of featureDataBuffer in a temporary buffer
        memcpy(tmpBuffer, featureDataBuffer, FEATURE_DATA_BUFFER_SIZE);

        int32_t nbAllocatedFeatures = LLKERNEL_IMPL_getAllocatedFeaturesCount();
        TEST_ASSERT_EQUAL_INT(installed_features, nbAllocatedFeatures);

        // Allocate new feature
        featureHandle = LLKERNEL_IMPL_allocateFeature__II(FEATURE_DATA_BUFFER_SIZE, FEATURE_DATA_BUFFER_SIZE);
        if(0 == featureHandle){
        	break;// no more space to allocate new feature
        }

        void *romAddr = LLKERNEL_IMPL_getFeatureAddressROM__I(featureHandle);
        TEST_ASSERT_NOT_NULL(romAddr);

        void *ramAddr = LLKERNEL_IMPL_getFeatureAddressRAM__I(featureHandle);
        TEST_ASSERT_NOT_NULL(ramAddr);

        // Check memory block overlap between RAM and ROM
        if(((((int32_t)romAddr) <= (int32_t)(ramAddr)) && (((int32_t)romAddr + FEATURE_DATA_BUFFER_SIZE) > (int32_t)(ramAddr))) ||
        		((((int32_t)ramAddr) <= (int32_t)(romAddr)) && (((int32_t)ramAddr + FEATURE_DATA_BUFFER_SIZE) > (int32_t)(romAddr)))){
        	TEST_ASSERT_MESSAGE(false, "Feature RAM and ROM area overlaped");
        }

        // Install feature
        int32_t result = LLKERNEL_IMPL_copyToROM__LiceTea_lang_Ram_2LiceTea_lang_Ram_2I(romAddr, featureDataBuffer, FEATURE_DATA_BUFFER_SIZE);
        TEST_ASSERT_MESSAGE(LLKERNEL_OK == result, "LLKERNEL_IMPL_copyToROM() returned an error");

        // Ensure that featureDataBuffer content has not been altered here
        if(0 != memcmp(featureDataBuffer, tmpBuffer, FEATURE_DATA_BUFFER_SIZE)){
        	TEST_ASSERT_MESSAGE(false, "Corrupted feature data passed");
        }

        result = LLKERNEL_IMPL_flushCopyToROM();
        TEST_ASSERT_MESSAGE(LLKERNEL_OK == result, "LLKERNEL_IMPL_flushCopyToROM() returned an error");

        // Ensure that featureDataBuffer content has not been altered after flush
		if(0 != memcmp(featureDataBuffer, tmpBuffer, FEATURE_DATA_BUFFER_SIZE)){
			TEST_ASSERT_MESSAGE(false, "Corrupted feature data passed after LLKERNEL_IMPL_flushCopyToROM()");
		}

        // Check feature installation consitency
        if(0 != memcmp(romAddr, featureDataBuffer, FEATURE_DATA_BUFFER_SIZE)){
        	TEST_ASSERT_MESSAGE(false, "Corrupted feature content");
        }

        installed_features++;
    } while(1);
}

/** @brief Allocate, install and free #NUMBER_OF_FEATURES features. */
static void T_LLKERNEL_CHECK_resource_allocate_and_free(void)
{
	UTIL_print_string("LLKERNEL resource allocate and free\n");

    for(int32_t i = 0; i < NUMBER_OF_FEATURES; i++) {
        sprintf((char*)featureDataBuffer, "********llkernel %d llkernel*******", i);

        // Allocate new feature
        featureHandles[i] = LLKERNEL_IMPL_allocateFeature__II(FEATURE_DATA_BUFFER_SIZE, FEATURE_DATA_BUFFER_SIZE);
        if (0 == featureHandles[i]) {
            TEST_ASSERT_MESSAGE(false, "LLKERNEL_IMPL_allocateFeature() returned an error");
        }

        int32_t nbAllocatedFeatures = LLKERNEL_IMPL_getAllocatedFeaturesCount();
		TEST_ASSERT_EQUAL_INT(1, nbAllocatedFeatures);

        void *featureRomAddr = (void*)LLKERNEL_IMPL_getFeatureAddressROM__I(featureHandles[i]);
        TEST_ASSERT_NOT_NULL(featureRomAddr);

        void *featureRamAddr = (void*)LLKERNEL_IMPL_getFeatureAddressRAM__I(featureHandles[i]);
        TEST_ASSERT_NOT_NULL(featureRamAddr);

        // Install feature
        int32_t result = LLKERNEL_IMPL_copyToROM__LiceTea_lang_Ram_2LiceTea_lang_Ram_2I(featureRomAddr, featureDataBuffer, FEATURE_DATA_BUFFER_SIZE);
        TEST_ASSERT_MESSAGE(LLKERNEL_OK == result, "LLKERNEL_IMPL_copyToROM() returned an error");

        result = LLKERNEL_IMPL_flushCopyToROM();
        TEST_ASSERT_MESSAGE(LLKERNEL_OK == result, "LLKERNEL_IMPL_flushCopyToROM() returned an error");

        // Check feature installation consistency
        if(0 != memcmp(featureRomAddr, featureDataBuffer, FEATURE_DATA_BUFFER_SIZE)){
        	TEST_ASSERT_MESSAGE(false, "Corrupted feature content");
        }

        // Free installed feature
        LLKERNEL_IMPL_freeFeature__I(featureHandles[i]);

        // Check that feature handle at index 0 is not valid
        int32_t featureHandle = LLKERNEL_IMPL_getFeatureHandle__I(0);
        TEST_ASSERT_EQUAL_INT(0, featureHandle);

        // Check that feature handle is useless since feature free called
        void *tmpFeatureRomAddr = LLKERNEL_IMPL_getFeatureAddressROM__I(featureHandles[i]);
        TEST_ASSERT_MESSAGE(NULL == tmpFeatureRomAddr, "Feature free not working as expected (valid ROM address returned)");

        void *tmpFeatureRamAddr = LLKERNEL_IMPL_getFeatureAddressRAM__I(featureHandles[i]);
        TEST_ASSERT_MESSAGE(NULL == tmpFeatureRamAddr, "Feature free not working as expected (valid RAM address returned)");

        // Reset feature handle array
        featureHandles[i] = 0;
    }
}


/** @brief Attempt to allocate more memory than the kernel feature block size (ROM/RAM). Expected results is a failure. Feature allocation
 * 			also requires the size of the feature header.
 */
static void T_LLKERNEL_CHECK_resource_allocate_overflow(void)
{
	UTIL_print_string("LLKERNEL resource allocate overflow\n");

    int32_t handle = LLKERNEL_IMPL_allocateFeature__II(INT_MAX, 0x0);
    TEST_ASSERT_EQUAL_INT(0, handle);
    
    handle = LLKERNEL_IMPL_allocateFeature__II(0x0, INT_MAX);
    TEST_ASSERT_EQUAL_INT(0, handle);
}

/** @brief Attempt to install a feature larger than the kernel feature block size. */
static void T_LLKERNEL_CHECK_resource_install_overflow(void)
{
	UTIL_print_string("LLKERNEL resource install overflow\n");

	sprintf((char*)featureDataBuffer, "********llkernel 0 llkernel*******");

	featureHandles[0] = LLKERNEL_IMPL_allocateFeature__II(FEATURE_DATA_BUFFER_SIZE, FEATURE_DATA_BUFFER_SIZE);
	if (0 == featureHandles[0]) {
		// Allocate new feature failed (no more space ?)
		TEST_ASSERT_MESSAGE(false, "LLKERNEL_IMPL_allocateFeature() returned an error");
	}

    void *featureRomAddr = (void*)LLKERNEL_IMPL_getFeatureAddressROM__I(featureHandles[0]);
    TEST_ASSERT_NOT_NULL(featureRomAddr);

    int32_t result = LLKERNEL_IMPL_copyToROM__LiceTea_lang_Ram_2LiceTea_lang_Ram_2I(featureRomAddr, featureDataBuffer, INT_MAX);
    if(LLKERNEL_ERROR != result){
    	// Failure expected here but call to LLKERNEL_IMPL_copyToROM() function succeed. Try to call LLKERNEL_IMPL_flushCopyToROM() => fail expected.
    	result = LLKERNEL_IMPL_flushCopyToROM();
    	TEST_ASSERT_EQUAL_INT(LLKERNEL_ERROR, result);
    }

    result = LLKERNEL_IMPL_copyToROM__LiceTea_lang_Ram_2LiceTea_lang_Ram_2I(featureRomAddr + (FEATURE_DATA_BUFFER_SIZE / 2), featureDataBuffer, (FEATURE_DATA_BUFFER_SIZE - 1));
    if(LLKERNEL_ERROR != result){
    	// Failure expected here but call to LLKERNEL_IMPL_copyToROM() function succeed. Try to call LLKERNEL_IMPL_flushCopyToROM() => fail expected.
    	result = LLKERNEL_IMPL_flushCopyToROM();
    	TEST_ASSERT_EQUAL_INT(LLKERNEL_ERROR, result);
    }
}

/** @brief Attempt to install a feature out of the defined ROM area:
 *  		- before
 *  		- after
 *  		- spanning over the end of the defined area
 */
static void T_LLKERNEL_CHECK_resource_install_out_of_bounds(void)
{
	UTIL_print_string("LLKERNEL resource install out of bounds\n");

	// Prerequisite is to start with no feature already allocated
    int32_t nbAllocatedFeatures = LLKERNEL_IMPL_getAllocatedFeaturesCount();
	TEST_ASSERT_EQUAL_INT(0, nbAllocatedFeatures);

	// Allocate the first feature
	featureHandles[0] = LLKERNEL_IMPL_allocateFeature__II(FEATURE_DATA_BUFFER_SIZE, FEATURE_DATA_BUFFER_SIZE);
	if (0 == featureHandles[0]) {
		// Allocate new feature failed (no more space ?)
		TEST_ASSERT_MESSAGE(false, "LLKERNEL_IMPL_allocateFeature() returned an error");
	}

	// Check that only one feature is now allocated
	nbAllocatedFeatures = LLKERNEL_IMPL_getAllocatedFeaturesCount();
	TEST_ASSERT_EQUAL_INT(1, nbAllocatedFeatures);

	// Get ROM address of the first allocated feature
	void *featureRomAddr = (void*)LLKERNEL_IMPL_getFeatureAddressROM__I(featureHandles[0]);
	TEST_ASSERT_NOT_NULL(featureRomAddr);

    // Try to copy a sequence of bytes outside ROM area (lower bounds)
    int32_t result = LLKERNEL_IMPL_copyToROM__LiceTea_lang_Ram_2LiceTea_lang_Ram_2I((void*)((uint32_t)featureRomAddr - 0x1000), featureDataBuffer, FEATURE_DATA_BUFFER_SIZE);
    if(LLKERNEL_ERROR != result){
    	// Failure expected here but call to LLKERNEL_IMPL_copyToROM() function succeed. Try to call LLKERNEL_IMPL_flushCopyToROM() => fail expected.
    	result = LLKERNEL_IMPL_flushCopyToROM();
    	TEST_ASSERT_EQUAL_INT(LLKERNEL_ERROR, result);
    }

    // Try to copy a sequence of bytes outside ROM area (upper bounds)
    result = LLKERNEL_IMPL_copyToROM__LiceTea_lang_Ram_2LiceTea_lang_Ram_2I(featureRomAddr, featureDataBuffer, INT_MAX);
    if(LLKERNEL_ERROR != result){
    	// Failure expected here but call to LLKERNEL_IMPL_copyToROM() function succeed. Try to call LLKERNEL_IMPL_flushCopyToROM() => fail expected.
    	result = LLKERNEL_IMPL_flushCopyToROM();
    	TEST_ASSERT_EQUAL_INT(LLKERNEL_ERROR, result);
    }

}

/** @brief Attempt to check that no feature handle can be retrieved if no feature have been installed.
 */
static void T_LLKERNEL_CHECK_resource_installation(void)
{
	UTIL_print_string("LLKERNEL resource installation\n");

	// Prerequisite is to start with no feature already allocated
    int32_t nbAllocatedFeatures = LLKERNEL_IMPL_getAllocatedFeaturesCount();
	TEST_ASSERT_EQUAL_INT(0, nbAllocatedFeatures);

    // Check that feature handle at index 0 is not valid
    int32_t featureHandle = LLKERNEL_IMPL_getFeatureHandle__I(0);
    TEST_ASSERT_EQUAL_INT(0, featureHandle);

	// Allocate the first feature
	featureHandles[0] = LLKERNEL_IMPL_allocateFeature__II(FEATURE_DATA_BUFFER_SIZE, FEATURE_DATA_BUFFER_SIZE);
	if (0 == featureHandles[0]) {
		// Allocate new feature failed (no more space ?)
		TEST_ASSERT_MESSAGE(false, "LLKERNEL_IMPL_allocateFeature() returned an error");
	}

	// Allocate the second feature
	featureHandles[1] = LLKERNEL_IMPL_allocateFeature__II(FEATURE_DATA_BUFFER_SIZE, FEATURE_DATA_BUFFER_SIZE);
	if (0 == featureHandles[1]) {
		// Allocate new feature failed (no more space ?)
		TEST_ASSERT_MESSAGE(false, "LLKERNEL_IMPL_allocateFeature() returned an error");
	}

	// Check that feature handle at index 0 is valid
	featureHandle = LLKERNEL_IMPL_getFeatureHandle__I(0);
	TEST_ASSERT_EQUAL_INT(featureHandles[0], featureHandle);

	// Check that feature handle at index 1 is valid
	featureHandle = LLKERNEL_IMPL_getFeatureHandle__I(1);
	TEST_ASSERT_EQUAL_INT(featureHandles[1], featureHandle);

    // Check that feature handle at index 2 is not valid
    featureHandle = LLKERNEL_IMPL_getFeatureHandle__I(2);
    TEST_ASSERT_EQUAL_INT(0, featureHandle);

    // Check that feature handle at wrong negative index -1 is not valid
    featureHandle = LLKERNEL_IMPL_getFeatureHandle__I(-1);
    TEST_ASSERT_EQUAL_INT(0, featureHandle);
}

TestRef T_LLKERNEL_tests(void)
{
	EMB_UNIT_TESTFIXTURES(fixture_llkernel) {
		new_TestFixture("T_LLKERNEL_resource_allocate", T_LLKERNEL_CHECK_resource_allocate),
		new_TestFixture("T_LLKERNEL_resource_allocate_and_free", T_LLKERNEL_CHECK_resource_allocate_and_free),
		new_TestFixture("T_LLKERNEL_resource_allocate_overflow", T_LLKERNEL_CHECK_resource_allocate_overflow),
		new_TestFixture("T_LLKERNEL_resource_install_overflow", T_LLKERNEL_CHECK_resource_install_overflow),
        new_TestFixture("T_LLKERNEL_resource_install_out_of_bounds", T_LLKERNEL_CHECK_resource_install_out_of_bounds),
        new_TestFixture("T_LLKERNEL_resource_installation", T_LLKERNEL_CHECK_resource_installation),
	};
	EMB_UNIT_TESTCALLER(llkernel_tests, "LLKERNEL tests", T_LLKERNEL_setUp, T_LLKERNEL_tearDown, fixture_llkernel);

	return (TestRef)&llkernel_tests;
}
