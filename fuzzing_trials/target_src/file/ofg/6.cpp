#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <magic.h>

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the null-terminated string
    char *file_path = (char *)malloc(size + 1);
    if (file_path == NULL) {
        return 0;
    }

    // Copy the data to the string and null-terminate it
    memcpy(file_path, data, size);
    file_path[size] = '\0';

    // Create a magic_set object
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        free(file_path);
        return 0;
    }

    // Call the function-under-test
    magic_compile(magic, file_path);

    // Clean up
    magic_close(magic);
    free(file_path);

    return 0;
}