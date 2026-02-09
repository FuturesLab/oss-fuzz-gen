#include <sqlite3.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int my_commit_hook(void *data) {
    // A simple commit hook that does nothing and returns 0
    return 0;
}

int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int (*commit_hook)(void *) = my_commit_hook; // Change to int return type
    void *hook_data = NULL;

    // Initialize SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Set the commit hook
    sqlite3_commit_hook(db, commit_hook, hook_data);

    // Create a table
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    sqlite3_exec(db, create_table_sql, 0, 0, 0);

    // Prepare an insert statement
    sqlite3_stmt *stmt;
    const char *insert_sql = "INSERT INTO test (value) VALUES (?);";

    if (sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Use the input data to insert into the table
    // Ensure the input data is null-terminated for SQLite
    char value[256];
    size_t value_size = size < sizeof(value) - 1 ? size : sizeof(value) - 1;
    memcpy(value, data, value_size);
    value[value_size] = '\0'; // Null-terminate the string

    // Bind the input data to the prepared statement
    sqlite3_bind_text(stmt, 1, value, -1, SQLITE_STATIC);

    // Execute the insert statement
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    // Clean up
    sqlite3_close(db);

    return 0;
}