#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Ensure the input is null-terminated and non-empty
    if (size == 0) {
        return 0;
    }

    // Create a buffer for the null-terminated string
    char *filename = (char *)malloc(size + 1);
    if (filename == NULL) {
        return 0;
    }

    // Copy the data into the buffer and null-terminate it
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Call the function-under-test
    sqlite3 *db;
    int rc = sqlite3_open(filename, &db);
    if (rc == SQLITE_OK) {
        sqlite3_close(db);
    }

    // Free the allocated memory
    free(filename);

    return 0;
}