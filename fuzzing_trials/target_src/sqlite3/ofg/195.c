#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_195(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    char *filename = NULL;

    // Ensure the data is null-terminated and non-empty
    if (size > 0) {
        filename = (char *)malloc(size + 1);
        if (filename == NULL) {
            return 0;
        }
        memcpy(filename, data, size);
        filename[size] = '\0'; // Null-terminate the string

        // Call the function-under-test
        int result = sqlite3_open(filename, &db);

        // Close the database if it was opened successfully
        if (result == SQLITE_OK) {
            sqlite3_close(db);
        }

        free(filename);
    }

    return 0;
}