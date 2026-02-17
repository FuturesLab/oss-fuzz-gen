#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_382(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    double result;
    int rc;

    // Initialize SQLite
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table and insert a value
    const char *create_table_sql = "CREATE TABLE test (value REAL);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    const char *insert_sql = "INSERT INTO test (value) VALUES (?);";
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare insert statement
    }

    // Bind a double value to the statement
    double value_to_insert = 0.0;
    if (size >= sizeof(double)) {
        value_to_insert = *(double *)data; // Use the first bytes of data as a double
    }
    sqlite3_bind_double(stmt, 1, value_to_insert);

    // Execute the insert statement
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_close(db);
        return 0; // Failed to execute insert statement
    }

    // Prepare a statement to select the value
    const char *select_sql = "SELECT value FROM test;";
    rc = sqlite3_prepare_v2(db, select_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare select statement
    }

    // Step through the results
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Call the function under test
        result = sqlite3_column_double(stmt, 0);
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0; // Fuzzer harness completed
}