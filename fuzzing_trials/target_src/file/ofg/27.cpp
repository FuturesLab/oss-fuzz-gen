#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <magic.h>

extern "C" {
    // Include the necessary headers for the project-under-test.
    // Assume that the magic.h header is part of the project-under-test.
    #include <magic.h>
}

// Function-under-test declaration
extern "C" int magic_list(struct magic_set *, const char *);

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Declare and initialize the variables required for the function-under-test
    struct magic_set *magic = NULL;
    char *filename = NULL;

    // Initialize the magic_set structure
    magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        return 0; // Exit if magic_open fails
    }

    // Allocate memory for the filename and ensure it's null-terminated
    filename = (char *)malloc(size + 1);
    if (filename == NULL) {
        magic_close(magic);
        return 0; // Exit if memory allocation fails
    }
    memcpy(filename, data, size);
    filename[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    magic_list(magic, filename);

    // Clean up
    free(filename);
    magic_close(magic);

    return 0;
}