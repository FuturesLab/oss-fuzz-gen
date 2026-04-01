#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const cmsCIEXYZ *d50_xyz = cmsD50_XYZ();

    // Access the returned cmsCIEXYZ structure to ensure it's being used
    if (d50_xyz != NULL) {
        volatile double x = d50_xyz->X;
        volatile double y = d50_xyz->Y;
        volatile double z = d50_xyz->Z;
        // Use the volatile keyword to prevent the compiler from optimizing away the access
    }

    return 0;
}