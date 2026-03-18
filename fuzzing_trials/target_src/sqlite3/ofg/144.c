#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to be used as a C-string
    char *filename = (char *)malloc(size + 1);
    if (filename == NULL) {
        return 0; // Handle allocation failure
    }

    // Copy data to filename and null-terminate
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Call the function-under-test
    // Here we should use the filename in a meaningful way with SQLite
    sqlite3 *db;
    int rc = sqlite3_open(filename, &db);
    if (rc == SQLITE_OK) {
        // Successfully opened the database, now close it
        sqlite3_close(db);
    }

    // Free the allocated memory
    free(filename);

    return 0;
}