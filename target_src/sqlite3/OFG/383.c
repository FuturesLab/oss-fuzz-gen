#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_383(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "CREATE TABLE test (value REAL); INSERT INTO test (value) VALUES (?);";
    int rc;

    // Open a new database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Bind the input data to the first parameter of the SQL statement
    double value = 0.0;
    if (size >= sizeof(double)) {
        // Ensure we have enough data to read a double
        value = *(double *)data; // Cast data to double
    }
    sqlite3_bind_double(stmt, 1, value);

    // Step the statement to execute it
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Failed to execute statement
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Prepare a new statement to retrieve the value
    const char *select_sql = "SELECT value FROM test;";
    rc = sqlite3_prepare_v2(db, select_sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare select statement
    }

    // Step the statement to execute it
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Call the function under test
        double result = sqlite3_column_double(stmt, 0);
        // We can use the result for further processing or validation if needed
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0; // Return success
}