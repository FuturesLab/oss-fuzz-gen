#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    sqlite3_int64 changes;

    // Initialize the SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Execute a simple SQL command to ensure there are changes
    const char *sql = "CREATE TABLE test(id INTEGER PRIMARY KEY, value TEXT);"
                      "INSERT INTO test(value) VALUES('test');";
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    changes = sqlite3_changes64(db);

    // Cleanup
    sqlite3_close(db);

    return 0;
}