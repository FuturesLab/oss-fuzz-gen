#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_305(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const void *declType;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table
    const char *createTableSQL = "CREATE TABLE test (id INTEGER, value TEXT);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a SQL statement with a simple query
    const char *sql = "SELECT * FROM test;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Use the fuzzing data to determine the column index
    int columnIndex = 0;
    if (size > 0) {
        columnIndex = data[0] % 2; // Since we only have 2 columns: id and value
    }

    // Call the function-under-test
    declType = sqlite3_column_decltype16(stmt, columnIndex);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}