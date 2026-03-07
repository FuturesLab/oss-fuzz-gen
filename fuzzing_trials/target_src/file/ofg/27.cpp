#include <stdint.h>
#include <stddef.h>
#include <magic.h>  // Assuming the magic.h header provides the declaration for magic_list and related structures
#include <stdlib.h> // For malloc and free
#include <string.h> // For memcpy

extern "C" {
    // Function signature from the task
    int magic_list(struct magic_set *, const char *);
    struct magic_set *magic_open(int);
    int magic_load(struct magic_set *, const char *);
    void magic_close(struct magic_set *);
}

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Initialize variables
    struct magic_set *ms;
    const char *filename;

    // Allocate and initialize a magic_set structure
    ms = magic_open(MAGIC_NONE);
    if (ms == NULL) {
        return 0;  // Return early if allocation fails
    }

    // Load the default magic database
    if (magic_load(ms, NULL) != 0) {
        magic_close(ms);
        return 0;  // Return early if loading fails
    }

    // Ensure the data is null-terminated for safe conversion to a string
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        magic_close(ms);
        return 0;  // Return early if allocation fails
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Set the filename to the null-terminated data
    filename = null_terminated_data;

    // Check if the filename is not empty and has a reasonable length to ensure the function is effectively tested
    if (filename[0] != '\0' && strlen(filename) < 256) {
        // Call the function-under-test
        int result = magic_list(ms, filename);
        if (result != 0) {
            // Handle the case where magic_list returns an error
            // This could involve logging or other error handling mechanisms
        }
    }

    // Clean up resources
    free(null_terminated_data);
    magic_close(ms);

    return 0;
}