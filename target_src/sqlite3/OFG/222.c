#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_222(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const void *blob;
    int columnIndex = 0; // Assuming we want to read the first column

    // Initialize SQLite
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, data BLOB);";
    sqlite3_exec(db, createTableSQL, 0, 0, 0);

    // Prepare an insert statement
    const char *insertSQL = "INSERT INTO test (data) VALUES (?);";
    if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Bind the blob data to the statement
    sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC);

    // Execute the insert statement
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    // Prepare a select statement to retrieve the blob
    const char *selectSQL = "SELECT data FROM test WHERE id = 1;";
    if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Step through the result
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Call the function under test
        blob = sqlite3_column_blob(stmt, columnIndex);
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}