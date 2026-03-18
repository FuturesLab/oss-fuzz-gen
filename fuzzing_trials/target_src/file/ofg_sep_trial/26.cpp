#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <magic.h>

extern "C" {
    // Include the necessary C headers and function declarations
    struct magic_set *magic_open(int flags);
    int magic_list(struct magic_set *, const char *);
    void magic_close(struct magic_set *);
}

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    struct magic_set *magic = NULL;
    char *filename = NULL;

    // Ensure the data size is sufficient to create a valid string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    filename = (char *)malloc(size + 1);
    if (filename == NULL) {
        return 0;
    }
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Initialize the magic_set structure
    magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        free(filename);
        return 0;
    }

    // Call the function-under-test
    magic_list(magic, filename);

    // Clean up resources
    magic_close(magic);
    free(filename);

    return 0;
}