#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char sql[256]; // Buffer for the SQL statement

    // Ensure the input data is null-terminated and fits within the SQL buffer
    size_t sql_length = size < sizeof(sql) - 30 ? size : sizeof(sql) - 30; // Reserve space for "SELECT * FROM test_table WHERE id = ?"
    memcpy(sql, data, sql_length);
    sql[sql_length] = '\0'; // Null-terminate the string

    // Prepare the SQL statement with the input data
    snprintf(sql + sql_length, sizeof(sql) - sql_length, " SELECT * FROM test_table WHERE id = '%s'", sql);

    // Open a database connection
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Handle database open failure
    }

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Handle SQL prepare failure
    }

    // Execute the statement
    sqlite3_step(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}