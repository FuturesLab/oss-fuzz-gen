#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <magic.h>

extern "C" {
    // Function signature from the project
    int magic_list(struct magic_set *, const char *);
}

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Initialize the magic_set structure
    struct magic_set *ms = magic_open(MAGIC_NONE);
    if (ms == NULL) {
        return 0;
    }

    // Load a default magic database
    if (magic_load(ms, NULL) != 0) {
        magic_close(ms);
        return 0;
    }

    // Create a null-terminated string from the input data
    char *input_str = (char *)malloc(size + 1);
    if (input_str == NULL) {
        magic_close(ms);
        return 0;
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';

    // Call the function-under-test
    magic_list(ms, input_str);

    // Clean up
    free(input_str);
    magic_close(ms);

    return 0;
}