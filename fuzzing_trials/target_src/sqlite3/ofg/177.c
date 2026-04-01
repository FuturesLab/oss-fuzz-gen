#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_177(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test(id INT); INSERT INTO test(id) VALUES(1); SELECT id FROM test;";

    // Open a new in-memory database
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
    rc = sqlite3_prepare_v2(db, "SELECT id FROM test;", -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Step through the results
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Use the data as the column index
        int column_index = (int)(data[0] % sqlite3_column_count(stmt));
        
        // Call the function-under-test
        int value = sqlite3_column_int(stmt, column_index);
        
        // Use value to prevent compiler optimizations
        (void)value;
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}