#include <stdint.h>
#include <stddef.h>
#include <magic.h>

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    struct magic_set *magic = magic_open(MAGIC_NONE);
    const char *error_message;

    if (magic == NULL) {
        return 0;
    }

    // Load a magic database, this is necessary before using magic functions
    if (magic_load(magic, NULL) != 0) {
        magic_close(magic);
        return 0;
    }

    // Call the function-under-test
    error_message = magic_error(magic);

    // Use error_message in some way to ensure it's not optimized away
    if (error_message != NULL) {
        // For fuzzing purposes, we don't need to do anything with the error_message
        // Just ensure the call is made
    }

    // Clean up
    magic_close(magic);

    return 0;
}