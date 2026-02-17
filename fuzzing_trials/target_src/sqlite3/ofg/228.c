#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_228(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM test WHERE id = ?";
    const char *param_name = "param_name";

    // Open a memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Create a table for testing
    if (sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY);", NULL, NULL, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind a parameter to the statement
    int index = sqlite3_bind_parameter_index(stmt, param_name);

    // Check the index value (it should be 1 since we have one parameter)
    if (index > 0) {
        // Optionally bind a value to the parameter
        sqlite3_bind_int(stmt, index, 1);
    }

    // Finalize the statement
    sqlite3_finalize(stmt);
    // Close the database connection
    sqlite3_close(db);

    return 0;
}