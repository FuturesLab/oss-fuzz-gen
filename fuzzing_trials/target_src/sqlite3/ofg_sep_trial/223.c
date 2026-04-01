#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_223(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "CREATE TABLE test (id INT, name TEXT); INSERT INTO test VALUES (1, 'Alice'); SELECT * FROM test;";
    const char *tail;
    const char *columnName;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &tail);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the SQL statement to create the table and insert data
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        // Do nothing, just step through the rows
    }

    // Reset the statement to execute the SELECT query
    sqlite3_reset(stmt);

    // Execute the SELECT query
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        // Get the column name for each column in the result set
        for (int i = 0; i < sqlite3_column_count(stmt); i++) {
            columnName = sqlite3_column_name(stmt, i);
            if (columnName) {
                printf("Column name: %s\n", columnName);
            }
        }
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Close the database
    sqlite3_close(db);

    return 0;
}