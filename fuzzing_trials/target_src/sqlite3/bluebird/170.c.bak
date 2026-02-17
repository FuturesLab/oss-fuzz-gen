#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <stdint.h> // Include for uint8_t

int LLVMFuzzerTestOneInput_170(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *decltype_result;

    // Initialize SQLite
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table
    const char *create_table_sql = "CREATE TABLE test (id INTEGER, name TEXT);";
    sqlite3_exec(db, create_table_sql, 0, 0, 0);

    // Prepare a statement
    const char *insert_sql = "INSERT INTO test (id, name) VALUES (?, ?);";
    if (sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Bind values to the statement
    sqlite3_bind_int(stmt, 1, 1); // Bind id
    if (size > 0) {
        sqlite3_bind_text(stmt, 2, (const char *)data, size, SQLITE_STATIC); // Bind name only if size > 0
    } else {
        sqlite3_bind_text(stmt, 2, "", 0, SQLITE_STATIC); // Bind an empty string if size is 0
    }

    // Execute the statement
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    // Prepare a SELECT statement
    const char *select_sql = "SELECT * FROM test;";
    if (sqlite3_prepare_v2(db, select_sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Step through the results
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Call the function-under-test
        decltype_result = sqlite3_column_decltype(stmt, 1); // Get the decltype of the second column
        // Optionally, you can use decltype_result for further processing or logging
    }

    // Cleanup
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}