#include <cstddef>
#include <cstdint>
#include <magic.h>
#include <cstdio>

extern "C" {
    const char * magic_buffer(struct magic_set *, const void *, size_t);
}

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        return 0;
    }

    // Attempt to load the default magic database
    if (magic_load(magic, NULL) != 0) {
        // If loading fails, print the error and continue to test the buffer
        fprintf(stderr, "Failed to load magic database: %s\n", magic_error(magic));
    }

    const char *result = magic_buffer(magic, data, size);

    // Optionally, you can do something with the result, like logging or further processing.
    if (result != NULL) {
        printf("Magic buffer result: %s\n", result);
    } else {
        fprintf(stderr, "Magic buffer returned NULL: %s\n", magic_error(magic));
    }

    magic_close(magic);
    return 0;
}