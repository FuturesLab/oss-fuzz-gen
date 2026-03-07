#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <magic.h>

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    // Ensure data is null-terminated for string operations
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Initialize a magic_set object
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        free(null_terminated_data);
        return 0;
    }

    // Call the function-under-test
    int result = magic_load(magic, null_terminated_data);

    // Clean up
    magic_close(magic);
    free(null_terminated_data);

    return 0;
}