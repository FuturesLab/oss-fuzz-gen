#include <cstddef>
#include <cstdint>
#include <magic.h>

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Ensure the size is not zero to avoid passing NULL to the function
    if (size == 0) {
        return 0;
    }

    // Initialize a magic_set object
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        return 0;
    }

    // Load the default magic database
    if (magic_load(magic, NULL) != 0) {
        magic_close(magic);
        return 0;
    }

    // Call the function-under-test with the given data
    const char *result = magic_buffer(magic, data, size);

    // Use the result in some way, even if it's just to ensure it's not optimized away
    if (result != NULL) {
        // For fuzzing purposes, we don't need to do anything with the result
    }

    // Clean up
    magic_close(magic);

    return 0;
}