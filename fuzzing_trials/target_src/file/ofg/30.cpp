#include <stdint.h>
#include <stddef.h>
#include <magic.h>

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Initialize a magic_set structure
    struct magic_set *ms = magic_open(MAGIC_NONE);
    if (ms == NULL) {
        return 0; // If magic_open fails, return immediately
    }

    // Ensure the data is not empty and size is sufficient
    if (size < sizeof(int)) {
        magic_close(ms);
        return 0;
    }

    // Extract an integer from the data
    int flags = *(int*)data;

    // Call the function-under-test
    magic_setflags(ms, flags);

    // Clean up
    magic_close(ms);

    return 0;
}