#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_304(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, name TEXT); INSERT INTO test (name) VALUES ('Alice'), ('Bob'), ('Charlie'); SELECT * FROM test;";
    const void *column_name;

    // Open a new in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Execute the SQL statement
    rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare the SELECT statement
    rc = sqlite3_prepare_v2(db, "SELECT * FROM test;", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Use the input data to determine the column index
    int column_index = data[0] % sqlite3_column_count(stmt);

    // Call the function-under-test
    column_name = sqlite3_column_name16(stmt, column_index);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}