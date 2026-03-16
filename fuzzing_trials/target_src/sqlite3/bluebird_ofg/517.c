#include "sqlite3.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_517(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    // Open a new in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Create a table
    const char *sql = "CREATE TABLE test (id INT, value TEXT);";
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Insert some data
    sql = "INSERT INTO test (id, value) VALUES (1, 'Hello');";
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    sqlite3_int64 changes = sqlite3_changes64(db);

    // Log the number of changes
    printf("Number of changes: %lld\n", changes);

    // Close the database
    sqlite3_close(db);

    return 0;
}