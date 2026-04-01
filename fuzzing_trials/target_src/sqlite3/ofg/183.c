#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_183(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    const char *dbName = "test.db";
    const char *zDbName;

    // Ensure data is not empty and null-terminate it for safety
    if (size == 0) {
        return 0;
    }

    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Open a connection to an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        free(input);
        return 0;
    }

    // Use the input data as the database name
    zDbName = input;

    // Call the function-under-test
    sqlite3_db_readonly(db, zDbName);

    // Clean up
    sqlite3_close(db);
    free(input);

    return 0;
}