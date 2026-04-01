#include <cstdint>
#include <cstdlib>
#include <magic.h>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    struct magic_set *ms = magic_open(MAGIC_NONE);

    // Ensure magic_set is created successfully
    if (ms == NULL) {
        return 0;
    }

    // Check if data size is sufficient to perform meaningful operations
    if (size > 0) {
        // Set flags based on input data
        int flags = static_cast<int>(data[0] % 8); // Use the first byte to determine flags
        magic_setflags(ms, flags);

        // Use the remaining data as a buffer to test magic_buffer
        const char *result = magic_buffer(ms, data, size);
        
        // Check if result is not NULL to ensure the function was invoked correctly
        if (result != NULL) {
            // Optionally, you can print or log the result for debugging purposes
            // printf("Magic result: %s\n", result);
        }
    }

    // Clean up
    magic_close(ms);

    return 0;
}