#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"
#include <stdio.h>  // Include for snprintf
#include <wchar.h>  // Include for wide character support

// Fuzzing harness for cmsDictAlloc function
int LLVMFuzzerTestOneInput_216(const uint8_t *data, size_t size) {
    // Initialize a cmsContext
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Use the input data to create a dummy key-value pair for the dictionary
    if (size < 2) {
        cmsDeleteContext(context);
        return 0;
    }

    // Allocate a dictionary and insert a key-value pair using the input data
    cmsHANDLE handle = cmsDictAlloc(context);
    if (handle != NULL) {
        wchar_t key[256];
        wchar_t value[256];
        swprintf(key, sizeof(key)/sizeof(wchar_t), L"Key_%02x", data[0]);
        swprintf(value, sizeof(value)/sizeof(wchar_t), L"Value_%02x", data[1]);

        // Create dummy cmsMLU objects for DisplayName and DisplayValue
        cmsMLU *displayName = cmsMLUalloc(context, 1);
        cmsMLU *displayValue = cmsMLUalloc(context, 1);

        // Correctly use cmsDictAddEntry to add the key-value pair
        cmsDictAddEntry(handle, key, value, displayName, displayValue);

        // Perform cleanup
        cmsMLUfree(displayName);
        cmsMLUfree(displayValue);
        cmsDictFree(handle);
    }

    cmsDeleteContext(context);

    return 0;
}