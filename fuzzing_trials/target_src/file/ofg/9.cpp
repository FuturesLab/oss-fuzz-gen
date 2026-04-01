#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <magic.h>

extern "C" {
    void magic_close(struct magic_set *);
}

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        return 0;
    }

    // Use the data and size in some way to ensure they are not null
    if (size > 0) {
        const char *magic_result = magic_buffer(magic, data, size);
        if (magic_result == NULL) {
            // Handle error if needed
        }
    }

    // Fuzz the magic_close function
    magic_close(magic);

    return 0;
}