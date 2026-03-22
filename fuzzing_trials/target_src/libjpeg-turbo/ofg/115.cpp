#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract three integers
    if (size < 3 * sizeof(int)) {
        return 0;
    }

    // Extract three integers from the data
    int componentID = *(reinterpret_cast<const int*>(data));
    int width = *(reinterpret_cast<const int*>(data + sizeof(int)));
    int subsamp = *(reinterpret_cast<const int*>(data + 2 * sizeof(int)));

    // Call the function-under-test
    int result = tjPlaneWidth(componentID, width, subsamp);

    // Use the result to avoid compiler optimizations
    volatile int sink = result;
    (void)sink;

    return 0;
}