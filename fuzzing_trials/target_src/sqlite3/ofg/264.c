#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_264(const uint8_t *data, size_t size) {
    // Ensure the data is not empty and null-terminated
    if (size == 0 || data[size - 1] != '\0') {
        return 0;
    }

    // Allocate memory for the null-terminated string
    char *filename = (char *)malloc(size + 1);
    if (filename == NULL) {
        return 0;
    }

    // Copy the data into the filename buffer and null-terminate it
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Call the function-under-test
    const char *journal_filename = sqlite3_filename_journal(filename);

    // Check the result to ensure it's not NULL, indicating a potential issue with the input
    if (journal_filename != NULL) {
        // We don't need to do anything with journal_filename, just ensure the function is called
    }

    // Free the allocated memory
    free(filename);

    return 0;
}