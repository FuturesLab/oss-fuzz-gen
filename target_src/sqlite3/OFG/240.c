#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_240(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const unsigned char *text;
    int rc;

    // Initialize SQLite and create an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Prepare an insert statement
    const char *insert_sql = "INSERT INTO test (value) VALUES (?);";
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Bind the input data to the statement
    sqlite3_bind_text(stmt, 1, (const char *)data, (size > 0) ? size : 1, SQLITE_STATIC);

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Failed to execute statement
    }

    // Prepare a select statement
    const char *select_sql = "SELECT value FROM test WHERE id = 1;";
    rc = sqlite3_prepare_v2(db, select_sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Failed to prepare select statement
    }

    // Step through the results
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Retrieve the text from the first column
        text = sqlite3_column_text(stmt, 0);
        // Optionally, you can do something with 'text' here
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}