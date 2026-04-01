#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    char *errMsg = 0;

    // Initialize the SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Create a sample table
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Insert a sample row
    sql = "INSERT INTO test (value) VALUES ('sample');";
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    sqlite3_int64 lastRowId = sqlite3_last_insert_rowid(db);
    printf("Last inserted row ID: %lld\n", lastRowId);

    // Clean up
    sqlite3_close(db);

    return 0;
}