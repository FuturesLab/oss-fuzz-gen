#include <stdint.h>
#include <stdlib.h>
#include <stddef.h> // Include this for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_156(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *columnName;
    int columnIndex = 0;

    // Open an in-memory SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table for testing
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, name TEXT)";
    sqlite3_exec(db, createTableSQL, 0, 0, 0);

    // Prepare a statement to insert data
    const char *insertSQL = "INSERT INTO test (name) VALUES (?)";
    if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Bind a value to the statement
    sqlite3_bind_text(stmt, 1, (const char *)data, size, SQLITE_STATIC);

    // Execute the statement
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    // Prepare a statement to select data
    const char *selectSQL = "SELECT * FROM test";
    if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Get the column name for the first column (index 0)
    columnName = sqlite3_column_name(stmt, columnIndex);

    // Optionally, you can use the column name in some way or just check it
    if (columnName != NULL) {
        // Do something with the column name if needed
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}