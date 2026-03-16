#include <stdint.h>
#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_232(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc;
    const char *sql = "CREATE TABLE test (id INT, name TEXT); INSERT INTO test (id, name) VALUES (1, 'Alice');";
    const char *tail = NULL;
    const char *column_name;
    int column_index = 0;
    int column_count;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Execute SQL to create table and insert data
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement using the input data
    rc = sqlite3_prepare_v2(db, (const char *)data, size, &stmt, &tail);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement to ensure it's valid and can be stepped through
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Check the number of columns and get the column name if valid
    column_count = sqlite3_column_count(stmt);
    if (column_index < column_count) {
        column_name = sqlite3_column_name(stmt, column_index);
        if (column_name != NULL) {
            printf("Column name: %s\n", column_name);
        }
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}