#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
    // Ensure size is not zero to pass a valid integer to tjAlloc
    if (size == 0) return 0;

    // Convert the first few bytes of data to an integer for tjAlloc
    int allocSize = static_cast<int>(data[0]);

    // Call the function-under-test
    unsigned char *allocatedMemory = tjAlloc(allocSize);

    // If memory was allocated, free it
    if (allocatedMemory != nullptr) {
        tjFree(allocatedMemory);
    }

    return 0;
}