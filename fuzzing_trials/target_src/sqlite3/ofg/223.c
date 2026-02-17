#include <stdint.h>
#include <stdlib.h>
#include <stddef.h> // Include stddef.h for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_223(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const void *blob;
    int column_index = 0; // Assuming we want to test the first column

    // Create a new SQLite database in memory
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a table and insert a blob
    const char *create_table_sql = "CREATE TABLE test_table (id INTEGER PRIMARY KEY, data BLOB);";
    sqlite3_exec(db, create_table_sql, 0, 0, 0);

    // Prepare an insert statement
    const char *insert_sql = "INSERT INTO test_table (data) VALUES (?);";
    if (sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Bind the input data as a blob
    sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC);

    // Execute the insert statement
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    // Prepare a select statement
    const char *select_sql = "SELECT data FROM test_table WHERE id = 1;";
    if (sqlite3_prepare_v2(db, select_sql, -1, &stmt, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Step through the result
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Call the function under test
        blob = sqlite3_column_blob(stmt, column_index);
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}