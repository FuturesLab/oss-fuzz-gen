#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
    // Initialize SQLite
    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Prepare a statement to create a table
    const char *createTableSQL = "CREATE TABLE test (id INTEGER, value BLOB)";
    sqlite3_exec(db, createTableSQL, 0, 0, 0);

    // Prepare a statement to insert data into the table
    sqlite3_stmt *stmt;
    const char *insertSQL = "INSERT INTO test (id, value) VALUES (?, ?)";
    sqlite3_prepare_v2(db, insertSQL, -1, &stmt, 0);

    // Bind an integer value and the fuzzing input data as a blob
    sqlite3_bind_int(stmt, 1, 1);
    sqlite3_bind_blob(stmt, 2, data, size, SQLITE_TRANSIENT);

    // Execute the statement
    sqlite3_step(stmt);

    // Prepare a statement to select the blob data
    const char *selectSQL = "SELECT value FROM test WHERE id = 1";
    sqlite3_prepare_v2(db, selectSQL, -1, &stmt, 0);

    // Execute the statement and fetch the blob data
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Get the blob data as an sqlite3_value
        const sqlite3_value *value = sqlite3_column_value(stmt, 0);

        // Call the function-under-test
        int bytes = sqlite3_value_bytes((sqlite3_value *)value);

        // Use the result to prevent optimization out
        (void)bytes;
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}