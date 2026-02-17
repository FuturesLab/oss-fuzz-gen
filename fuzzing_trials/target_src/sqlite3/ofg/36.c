#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const void *column_name;
    int column_index = 0; // We will use a fixed column index for fuzzing

    // Initialize SQLite
    sqlite3_initialize();

    // Create an in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table and insert a row
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, name TEXT);";
    sqlite3_exec(db, create_table_sql, 0, 0, 0);

    const char *insert_sql = "INSERT INTO test (name) VALUES ('example');";
    sqlite3_exec(db, insert_sql, 0, 0, 0);

    // Prepare a statement to select from the table
    const char *select_sql = "SELECT * FROM test;";
    if (sqlite3_prepare_v2(db, select_sql, -1, &stmt, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Step through the result set
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Call the function under test
        column_name = sqlite3_column_name16(stmt, column_index);
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}