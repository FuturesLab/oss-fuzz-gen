#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_272(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Execute a simple SQL statement to ensure there are changes
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);"
                      "INSERT INTO test (value) VALUES ('sample');";
    char *errMsg = NULL;
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    int total_changes = sqlite3_total_changes(db);
    printf("Total changes: %d\n", total_changes);

    // Clean up and close the database
    sqlite3_close(db);

    return 0;
}