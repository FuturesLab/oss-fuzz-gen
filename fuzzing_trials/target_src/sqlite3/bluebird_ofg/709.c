#include <stdint.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_709(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const void *result;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare a simple SQL statement
    const char *sql = "CREATE TABLE test (id INTEGER, name TEXT);";
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare an INSERT statement to ensure the table has a column
    sql = "INSERT INTO test (id, name) VALUES (1, 'example');";
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a SELECT statement
    sql = "SELECT * FROM test;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Use data to determine the column index
    int column_index = 0;
    if (size > 0) {
        column_index = data[0] % sqlite3_column_count(stmt);
    }

    // Step through the result to ensure the statement is executed
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    result = sqlite3_column_decltype16(stmt, column_index);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}