#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to extract three integers
    if (size < 3 * sizeof(int)) {
        return 0;
    }

    // Extract three integers from the input data
    int componentID = *((int*)data);
    int width = *((int*)(data + sizeof(int)));
    int subsamp = *((int*)(data + 2 * sizeof(int)));

    // Call the function-under-test with the extracted integers
    int result = tjPlaneWidth(componentID, width, subsamp);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}