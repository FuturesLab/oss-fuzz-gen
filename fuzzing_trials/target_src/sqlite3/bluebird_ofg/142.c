#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, name TEXT);";
    const char *insert_sql = "INSERT INTO test (name) VALUES (?);";
    const void *result;
    int rc;

    // Initialize SQLite
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

    // Prepare the insert statement
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Bind the data to the statement
    // Ensure that the size is within a reasonable limit for SQLite
    if (size > 0 && size < 1024) {
        // Bind the input data as a text value
        rc = sqlite3_bind_text(stmt, 1, (const char *)data, size, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return 0; // Failed to bind data
        }

        // Execute the statement
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return 0; // Failed to execute statement
        }
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Prepare a statement to select the text back
    const char *select_sql = "SELECT name FROM test WHERE id = 1;";
    rc = sqlite3_prepare_v2(db, select_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare select statement
    }

    // Execute the select statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Call the function under test
        result = sqlite3_column_text16(stmt, 0);
        // Here you can use 'result' for further processing if needed
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}