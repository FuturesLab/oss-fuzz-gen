#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> // Include the standard I/O library for 'stderr'

extern "C" {
    #include <magic.h> // Ensure magic.h is included within extern "C"

    // Function signature from the task
    int magic_check(struct magic_set *, const char *);
}

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    // Initialize a magic_set structure
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        return 0; // If initialization fails, return early
    }

    // Ensure the magic_set is loaded with default magic database
    if (magic_load(magic, NULL) != 0) {
        magic_close(magic);
        return 0; // If loading fails, return early
    }

    // Allocate memory for the input string and ensure it's null-terminated
    char *input_str = (char *)malloc(size + 1);
    if (input_str == NULL) {
        magic_close(magic);
        return 0; // If allocation fails, return early
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0'; // Null-terminate the string

    // Create a temporary file to simulate a real file input
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        free(input_str);
        magic_close(magic);
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(input_str, 1, size, temp_file);
    fflush(temp_file);

    // Get the file descriptor and construct a path
    int fd = fileno(temp_file);
    char path[256];
    snprintf(path, sizeof(path), "/proc/self/fd/%d", fd);

    // Call the function-under-test with the file path
    int result = magic_check(magic, path);
    
    // Use the result to ensure the function is being exercised
    if (result != 0) {
        // Handle the error or log it if needed
        // Log the error message from magic
        const char *error = magic_error(magic);
        if (error != NULL) {
            fprintf(stderr, "magic_check error: %s\n", error);
        }
    }

    // Clean up
    fclose(temp_file);
    free(input_str);
    magic_close(magic);

    return 0;
}