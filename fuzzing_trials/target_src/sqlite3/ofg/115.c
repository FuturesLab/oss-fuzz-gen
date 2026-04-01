#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    // Initialize the SQLite database connection and statement
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value TEXT); INSERT INTO test (value) VALUES (?);";

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

    // Ensure the index is within a valid range
    int index = 1; // For this SQL, the first parameter index is 1

    // Bind the input data as a text to the SQL statement
    rc = sqlite3_bind_text(stmt, index, (const char *)data, size, SQLITE_TRANSIENT);

    // Execute the SQL statement
    rc = sqlite3_step(stmt);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}