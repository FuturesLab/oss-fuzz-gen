#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_245(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER, value TEXT);"
                      "INSERT INTO test (id, value) VALUES (1, 'Hello');"
                      "SELECT value FROM test WHERE id = 1;";
    const unsigned char *text;

    // Initialize SQLite in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Execute SQL to create table and insert data
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, "SELECT value FROM test WHERE id = ?", -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the first parameter to the integer value from the fuzzing data
    int id = (size > 0) ? data[0] : 1; // Use the first byte of data as the id, default to 1
    sqlite3_bind_int(stmt, 1, id);

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Call the function-under-test
        text = sqlite3_column_text(stmt, 0);
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}