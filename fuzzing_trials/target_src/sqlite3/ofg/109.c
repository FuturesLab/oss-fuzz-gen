#include <stdint.h>
#include <stddef.h>  // Include this header to define size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    char *errMsg = 0;

    // Open a new in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare a simple SQL statement
    const char *sql = "CREATE TABLE IF NOT EXISTS test(id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Close the database connection
    sqlite3_close(db);

    return 0;
}