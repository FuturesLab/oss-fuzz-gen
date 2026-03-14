#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_193(const uint8_t *data, size_t size) {
    // Declare and initialize a cmsToneCurve pointer
    cmsToneCurve *originalCurve = NULL;

    // Check if the size is sufficient to create a tone curve
    if (size >= 2) {
        // Use the first byte to determine the number of segments (for simplicity, limit to 10)
        int numSegments = data[0] % 10 + 1;

        // Allocate memory for the segments
        cmsFloat32Number *segments = (cmsFloat32Number *)malloc(numSegments * sizeof(cmsFloat32Number));
        if (segments == NULL) {
            return 0; // Memory allocation failed
        }

        // Use the remaining data to fill the segments
        for (int i = 0; i < numSegments && i + 1 < size; i++) {
            segments[i] = data[i + 1] / 255.0f; // Normalize to [0, 1]
        }

        // Create a tone curve using the segments
        originalCurve = cmsBuildTabulatedToneCurve16(NULL, numSegments, segments);

        // Free the allocated memory for segments
        free(segments);
    }

    // Ensure originalCurve is not NULL before calling the function
    if (originalCurve != NULL) {
        // Call the function-under-test
        cmsToneCurve *duplicatedCurve = cmsDupToneCurve(originalCurve);

        // Free the duplicated curve
        if (duplicatedCurve != NULL) {
            cmsFreeToneCurve(duplicatedCurve);
        }

        // Free the original curve
        cmsFreeToneCurve(originalCurve);
    }

    return 0;
}