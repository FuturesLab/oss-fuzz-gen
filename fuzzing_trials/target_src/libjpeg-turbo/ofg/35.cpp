#include <cstdint>
#include <cstdlib>
#include <cstdio>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    // Declare and initialize input variables for tjPlaneSizeYUV
    int width = 1;  // Width of the image, must be > 0
    int height = 1; // Height of the image, must be > 0
    int subsamp = TJSAMP_444; // Subsampling option, using a valid constant from turbojpeg
    int align = 1;  // Alignment, typically 1, 2, 4, or 8

    // Ensure data is not empty to extract meaningful values
    if (size >= 5) {
        // Extract values from data to vary the inputs
        width = data[0] + 1;  // Avoid zero
        height = data[1] + 1; // Avoid zero
        subsamp = data[2] % 6; // Valid subsampling values are 0-5
        align = (data[3] % 4) + 1; // Valid alignments are 1, 2, 3, 4
    }

    // Call the function-under-test
    unsigned long result = tjPlaneSizeYUV(0, width, height, subsamp, align);

    // Print the result (optional, for debugging purposes)
    printf("Result: %lu\n", result);

    return 0;
}