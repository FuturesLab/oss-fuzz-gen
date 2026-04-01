#include <stddef.h>
#include <stdint.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    if (size < 3) {
        // Not enough data to extract three integers
        return 0;
    }

    // Extract three integers from the input data
    int componentID = static_cast<int>(data[0]);
    int subsamp = static_cast<int>(data[1]);
    int height = static_cast<int>(data[2]);

    // Call the function-under-test
    int result = tjPlaneHeight(componentID, subsamp, height);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}