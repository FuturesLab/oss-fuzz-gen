#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_176(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    int columnIndex;
    char *errMsg = 0;

    // Initialize an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table
    const char *createTableSQL = "CREATE TABLE test (id INTEGER, value TEXT);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Insert a row into the table
    const char *insertSQL = "INSERT INTO test (id, value) VALUES (1, 'test');";
    rc = sqlite3_exec(db, insertSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement
    const char *selectSQL = "SELECT * FROM test;";
    rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Use data to determine the column index
        columnIndex = (size > 0) ? data[0] % sqlite3_column_count(stmt) : 0;

        // Call the function-under-test
        int result = sqlite3_column_int(stmt, columnIndex);

        // Print the result for debugging purposes
        printf("Column index: %d, Result: %d\n", columnIndex, result);
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}