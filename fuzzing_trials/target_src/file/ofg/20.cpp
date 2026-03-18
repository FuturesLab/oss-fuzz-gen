#include <stdint.h>
#include <stddef.h>
#include <magic.h>

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    struct magic_set *ms;
    int descriptor;
    const char *result;

    // Initialize the magic_set
    ms = magic_open(MAGIC_NONE);
    if (ms == NULL) {
        return 0; // If magic_open fails, return immediately
    }

    // Load the default magic database
    if (magic_load(ms, NULL) != 0) {
        magic_close(ms);
        return 0; // If magic_load fails, return immediately
    }

    // Ensure the descriptor is a valid integer within a reasonable range
    descriptor = size > 0 ? static_cast<int>(data[0]) : 0;

    // Call the function-under-test
    result = magic_descriptor(ms, descriptor);

    // Clean up
    magic_close(ms);

    return 0;
}