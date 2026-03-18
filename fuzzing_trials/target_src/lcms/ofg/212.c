#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

// Define the fuzzing function
int LLVMFuzzerTestOneInput_212(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsHTRANSFORM handle;
    cmsCIELab cielab;

    // Ensure the size is sufficient for cmsCIELab structure
    if (size < sizeof(cmsCIELab)) {
        return 0;
    }

    // Initialize the handle with a non-NULL value
    handle = cmsCreateTransform(NULL, TYPE_Lab_DBL, NULL, TYPE_Lab_DBL, INTENT_PERCEPTUAL, 0);
    if (handle == NULL) {
        return 0;
    }

    // Populate the cmsCIELab structure with data from the input
    cielab.L = ((double*)data)[0];
    cielab.a = ((double*)data)[1];
    cielab.b = ((double*)data)[2];

    // Call the function under test
    cmsBool result = cmsGDBAddPoint(handle, &cielab);

    // Clean up
    cmsDeleteTransform(handle);

    return 0;
}