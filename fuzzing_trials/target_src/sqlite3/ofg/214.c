#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_214(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Execute a simple query to initialize the database
    char *errMsg = 0;
    rc = sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);", 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Use the input data to insert into the database
    if (size > 0) {
        char query[256];
        snprintf(query, sizeof(query), "INSERT INTO test (value) VALUES ('%.*s');", (int)size, data);
        rc = sqlite3_exec(db, query, 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            sqlite3_free(errMsg);
        }
    }

    // Call the function-under-test
    int errcode = sqlite3_extended_errcode(db);

    // Use the errcode in some way to prevent compiler optimizations from removing the call
    if (errcode != SQLITE_OK) {
        // Handle the error code, if necessary
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}