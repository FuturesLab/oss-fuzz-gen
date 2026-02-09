#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <stddef.h> // Include for size_t

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const void *columnName;
    int columnIndex = 0; // Initialize column index

    // Initialize SQLite database in memory
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table and insert a row
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, name TEXT);";
    sqlite3_exec(db, createTableSQL, 0, 0, 0);

    const char *insertSQL = "INSERT INTO test (name) VALUES ('example');";
    sqlite3_exec(db, insertSQL, 0, 0, 0);

    // Prepare a statement
    const char *selectSQL = "SELECT * FROM test;";
    if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Step through the result set
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Call the function under test
        columnName = sqlite3_column_name16(stmt, columnIndex);
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0; // End of the fuzzing function
}