#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_220(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value TEXT);"
                      "INSERT INTO test (value) VALUES ('example');"
                      "SELECT * FROM test;";
    
    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Execute SQL to create table and insert data
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, "SELECT * FROM test;", -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Step through the result set and call the function-under-test
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Use data from the fuzzer to determine the column index
        int column_index = (size > 0) ? (data[0] % sqlite3_column_count(stmt)) : 0;
        sqlite3_value *value = sqlite3_column_value(stmt, column_index);

        // Use the value in some way (in this case, just ensure it's not NULL)
        if (value != NULL) {
            // This is just to demonstrate the call, no actual operation is performed on `value`
        }
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}