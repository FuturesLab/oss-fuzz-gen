#include <stdint.h>
#include <sqlite3.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_275(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value INTEGER); INSERT INTO test (value) VALUES (?);";

    // Open a new in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Ensure data is large enough to extract an integer
    if (size < sizeof(sqlite_int64)) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Extract an integer from the input data
    sqlite_int64 value = *(const sqlite_int64 *)data;

    // Bind the integer to the SQL statement
    sqlite3_bind_int64(stmt, 1, value);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}