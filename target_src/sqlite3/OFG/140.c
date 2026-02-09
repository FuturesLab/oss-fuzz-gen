#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    sqlite3_int64 result;

    // Initialize SQLite
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table
    const char *create_table_sql = "CREATE TABLE test (id INTEGER);";
    sqlite3_exec(db, create_table_sql, 0, 0, 0);

    // Use the input data to insert a value
    // Ensure that the value is within a valid range for an integer
    int value_to_insert = (size > 0) ? (data[0] % 100) : 0; // Example: use the first byte of data
    char insert_sql[100];
    snprintf(insert_sql, sizeof(insert_sql), "INSERT INTO test (id) VALUES (%d);", value_to_insert);
    sqlite3_exec(db, insert_sql, 0, 0, 0);

    // Prepare a statement to select the value
    const char *select_sql = "SELECT id FROM test;";
    if (sqlite3_prepare_v2(db, select_sql, -1, &stmt, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Execute the statement
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Call the function under test with a valid statement and a valid column index
        result = sqlite3_column_int64(stmt, 0);
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}