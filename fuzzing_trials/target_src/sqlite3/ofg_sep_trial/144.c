#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to be used as a C string
    char *filename = (char *)malloc(size + 1);
    if (filename == NULL) {
        return 0;
    }

    memcpy(filename, data, size);
    filename[size] = '\0';

    // Open a SQLite database with the filename
    sqlite3 *db;
    int rc = sqlite3_open(filename, &db);

    // If the database was opened successfully, close it
    if (rc == SQLITE_OK) {
        sqlite3_close(db);
    }

    // Free the allocated memory
    free(filename);

    return 0;
}