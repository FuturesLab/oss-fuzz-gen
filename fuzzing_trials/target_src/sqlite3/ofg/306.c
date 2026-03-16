#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_306(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql;
    const void *declType;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table
    sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare an insert statement
    sql = "INSERT INTO test (value) VALUES (?);";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data to the statement
    rc = sqlite3_bind_text(stmt, 1, (const char *)data, size, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Reset the statement to reuse it
    sqlite3_reset(stmt);

    // Prepare a select statement
    sql = "SELECT * FROM test;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the select statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Call the function-under-test
        declType = sqlite3_column_decltype16(stmt, 1);
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}