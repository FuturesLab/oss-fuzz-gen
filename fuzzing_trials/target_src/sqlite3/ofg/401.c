#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_401(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    int columnIndex = 0;

    // Initialize the SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value INTEGER);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Prepare an insert statement
    const char *insertSQL = "INSERT INTO test (value) VALUES (?);";
    rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Bind the data to the prepared statement
    sqlite3_bind_int(stmt, 1, (int)(data[0] % 100)); // Use the first byte of data for the value

    // Execute the insert statement
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    // Prepare a select statement
    const char *selectSQL = "SELECT value FROM test WHERE id = 1;";
    rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare select statement
    }

    // Step through the result
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Call the function under test
        int value = sqlite3_column_int(stmt, columnIndex);
        // Do something with the value if needed
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}