#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lcms2.h"

// Define a non-NULL cmsHANDLE for testing purposes
cmsHANDLE createTestHandle() {
    // Create a dummy context for testing
    cmsContext context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return NULL;
    }
    return context;
}

int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for the cmsCIEXYZ structure
    if (size < sizeof(cmsCIEXYZ)) {
        return 0;
    }

    // Initialize cmsCIEXYZ from the input data
    cmsCIEXYZ inputXYZ;
    memcpy(&inputXYZ, data, sizeof(cmsCIEXYZ));

    // Initialize cmsJCh structure
    cmsJCh outputJCh;
    outputJCh.J = 0.0;
    outputJCh.C = 0.0;
    outputJCh.h = 0.0;

    // Create a test handle
    cmsHANDLE testHandle = createTestHandle();
    if (testHandle == NULL) {
        return 0; // If handle creation failed, exit early
    }

    // Ensure the inputXYZ values are in a valid range to avoid overflow
    inputXYZ.X = fmin(fmax(inputXYZ.X, 0.0), 1.0);
    inputXYZ.Y = fmin(fmax(inputXYZ.Y, 0.0), 1.0);
    inputXYZ.Z = fmin(fmax(inputXYZ.Z, 0.0), 1.0);

    // Prepare a cmsViewingConditions structure
    cmsViewingConditions viewingConditions;
    viewingConditions.whitePoint = inputXYZ; // Correct assignment without &
    viewingConditions.Yb = 20.0; // Example value for background luminance
    viewingConditions.La = 40.0; // Example value for adapting luminance
    viewingConditions.surround = 1; // Example surround value
    viewingConditions.D_value = 1.0; // Example D_value

    // Initialize the CIECAM02 model
    cmsHANDLE camHandle = cmsCIECAM02Init(testHandle, &viewingConditions);
    if (camHandle != NULL) {
        // Call the function under test with valid viewing conditions
        cmsCIECAM02Forward(camHandle, &inputXYZ, &outputJCh);
        // Free the CIECAM02 handle
        cmsCIECAM02Done(camHandle);
    }

    // Free the test handle
    cmsDeleteContext(testHandle);

    return 0;
}