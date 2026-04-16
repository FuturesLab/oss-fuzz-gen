#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// Function prototype for the function-under-test
char ** hts_readlist(const char *filename, int is_file, int *n);

// Fuzzer entry point
int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz input
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If file creation fails, exit
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0; // If writing fails, exit
    }
    close(fd);

    int n = 0;
    int is_file = 1; // Indicate that the input is from a file

    // Call the function-under-test with the temporary file
    char **result = hts_readlist(tmpl, is_file, &n);

    // Cleanup: free the result if it's not NULL
    if (result != NULL) {
        for (int i = 0; i < n; ++i) {
            free(result[i]);
        }
        free(result);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}