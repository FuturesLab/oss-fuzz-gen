#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>  // Include the Little CMS library header

// Function-under-test
void cmsXYZ2xyY(cmsCIExyY *dest, const cmsCIEXYZ *source);

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsCIExyY dest;
    cmsCIEXYZ source;

    // Ensure there is enough data to fill the cmsCIEXYZ structure
    if (size < sizeof(cmsCIEXYZ)) {
        return 0;
    }

    // Copy data into the cmsCIEXYZ structure
    // Assuming data is in the correct format for cmsCIEXYZ
    source.X = ((const double *)data)[0];
    source.Y = ((const double *)data)[1];
    source.Z = ((const double *)data)[2];

    // Call the function-under-test
    cmsXYZ2xyY(&dest, &source);

    return 0;
}