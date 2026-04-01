#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>  // Include for malloc and free
#include <magic.h>

extern "C" {
    // Forward declaration of the function-under-test
    int magic_check(struct magic_set *, const char *);
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated for string operations
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Exit early if memory allocation fails
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Initialize a magic_set object
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        free(null_terminated_data);
        return 0; // Exit early if magic_open fails
    }

    // Call the function-under-test
    magic_check(magic, null_terminated_data);

    // Clean up resources
    magic_close(magic);
    free(null_terminated_data);

    return 0;
}