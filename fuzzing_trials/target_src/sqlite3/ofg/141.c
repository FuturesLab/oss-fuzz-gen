#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    sqlite3_stmt *stmt = NULL;
    sqlite3 *db = NULL;
    sqlite3_int64 result;
    int columnIndex = 0;

    // Initialize the SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table
    const char *createTableSQL = "CREATE TABLE test (id INTEGER);";
    sqlite3_exec(db, createTableSQL, 0, 0, 0);

    // Use the input data to insert into the table
    if (size > 0) {
        int id = (int)(data[0] % 100); // Use the first byte of input data as an ID
        char insertSQL[100];
        snprintf(insertSQL, sizeof(insertSQL), "INSERT INTO test (id) VALUES (%d);", id);
        sqlite3_exec(db, insertSQL, 0, 0, 0);
    }

    // Prepare a statement to select from the table
    const char *selectSQL = "SELECT id FROM test;";
    if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Execute the statement
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Ensure the column index is within bounds
        if (columnIndex >= 0) {
            // Call the function under test
            result = sqlite3_column_int64(stmt, columnIndex);
        }
    }

    // Cleanup
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}