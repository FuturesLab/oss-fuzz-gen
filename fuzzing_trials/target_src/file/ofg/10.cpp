#include <stdint.h>
#include <stddef.h>
#include <magic.h>

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    struct magic_set *ms;

    // Initialize the magic_set structure
    ms = magic_open(MAGIC_NONE);
    if (ms == NULL) {
        return 0;
    }

    // Load default magic database
    if (magic_load(ms, NULL) != 0) {
        magic_close(ms);
        return 0;
    }

    // Use the magic_set (for example, to get file type)
    if (size > 0) {
        magic_buffer(ms, data, size);
    }

    // Call the function-under-test
    magic_close(ms);

    return 0;
}