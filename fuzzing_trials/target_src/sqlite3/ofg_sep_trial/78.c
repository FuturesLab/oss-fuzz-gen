#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_78(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql;
    const char *decl_type;
    int column_index;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table
    sql = "CREATE TABLE test (id INTEGER, name TEXT, value REAL);";
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare an SQL statement
    sql = "SELECT id, name, value FROM test;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Ensure there's at least one column
    if (sqlite3_column_count(stmt) > 0) {
        // Use the provided data to determine column index
        column_index = data[0] % sqlite3_column_count(stmt);

        // Call the function-under-test
        decl_type = sqlite3_column_decltype(stmt, column_index);

        // Print the result for debugging
        if (decl_type != NULL) {
            printf("Column %d decltype: %s\n", column_index, decl_type);
        }
    }

    // Cleanup
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}