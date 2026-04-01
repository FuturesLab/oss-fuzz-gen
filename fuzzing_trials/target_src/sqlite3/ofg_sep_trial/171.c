#include <stdint.h>
#include <sqlite3.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_171(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    char *errMsg = 0;

    // Open a new in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Execute a simple SQL statement to make some changes
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);"
                      "INSERT INTO test (value) VALUES ('test1');"
                      "INSERT INTO test (value) VALUES ('test2');";
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    sqlite3_int64 changes = sqlite3_total_changes64(db);

    // Cleanup
    sqlite3_close(db);

    return 0;
}