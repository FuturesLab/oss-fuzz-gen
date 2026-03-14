extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    // Ensure size is non-zero and within a reasonable range for allocation
    if (size == 0 || size > 1024) {
        return 0;
    }

    // Convert size to int, ensuring it stays within the valid range for tjAlloc
    int allocSize = static_cast<int>(size);

    // Call the function-under-test
    unsigned char *allocatedMemory = tjAlloc(allocSize);

    // Check if allocation was successful
    if (allocatedMemory != nullptr) {
        // Do something with allocatedMemory if necessary
        // ...

        // Free the allocated memory after use
        tjFree(allocatedMemory);
    }

    return 0;
}