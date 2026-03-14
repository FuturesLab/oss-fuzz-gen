#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    // Ensure the size is non-zero to avoid tjAlloc(0) which might return NULL
    if (size == 0) {
        return 0;
    }

    // Use the size as the input for tjAlloc
    int allocationSize = static_cast<int>(size);

    // Call the function-under-test
    unsigned char *allocatedMemory = tjAlloc(allocationSize);

    // Check if the allocation was successful
    if (allocatedMemory != NULL) {
        // Perform operations on allocatedMemory if needed
        // ...

        // Free the allocated memory
        tjFree(allocatedMemory);
    }

    return 0;
}