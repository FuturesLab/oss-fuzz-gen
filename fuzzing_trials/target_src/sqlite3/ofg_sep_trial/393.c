#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_393(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "SELECT * FROM test WHERE column = ?";
    int index = 1; // Default index to bind parameter

    // Open a new in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a table for testing
    rc = sqlite3_exec(db, "CREATE TABLE test (column TEXT);", 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Use data to determine the index
    if (size > 0) {
        index = data[0] % 10; // Example to ensure index is within a reasonable range
    }

    // Call the function-under-test
    const char *paramName = sqlite3_bind_parameter_name(stmt, index);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}