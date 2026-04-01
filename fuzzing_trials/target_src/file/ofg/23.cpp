#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <magic.h>

extern "C" {
    // Function signature to be fuzzed
    int magic_getparam(struct magic_set *, int, void *);
}

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    struct magic_set *magic = magic_open(MAGIC_NONE);
    int param = 0;
    void *value = malloc(256); // Allocate memory for the value

    if (magic == NULL || value == NULL) {
        if (magic != NULL) {
            magic_close(magic);
        }
        free(value);
        return 0;
    }

    // Ensure the magic_set is initialized
    if (magic_load(magic, NULL) != 0) {
        magic_close(magic);
        free(value);
        return 0;
    }

    // Call the function-under-test
    magic_getparam(magic, param, value);

    // Clean up
    magic_close(magic);
    free(value);

    return 0;
}