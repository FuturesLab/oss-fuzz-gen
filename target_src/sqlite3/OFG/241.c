#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <stdint.h> // Include for uint8_t type

int LLVMFuzzerTestOneInput_241(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const unsigned char *text;
    int rc;
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, name TEXT);";
    const char *insert_sql = "INSERT INTO test (name) VALUES (?);";
    const char *select_sql = "SELECT name FROM test WHERE id = 1;";

    // Open a temporary in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create table
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Prepare insert statement
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare insert statement
    }

    // Bind the input data to the prepared statement
    sqlite3_bind_text(stmt, 1, (const char *)data, (int)size, SQLITE_STATIC);

    // Execute the insert statement
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt); // Finalize the statement

    // Prepare select statement
    rc = sqlite3_prepare_v2(db, select_sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare select statement
    }

    // Execute the select statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Call the function under test
        text = sqlite3_column_text(stmt, 0);
        // Optionally, do something with `text` here
    }

    sqlite3_finalize(stmt); // Finalize the statement
    sqlite3_close(db); // Close the database

    return 0;
}