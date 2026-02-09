#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_367(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    double value;

    // Initialize SQLite
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple prepared statement
    const char *sql = "SELECT ?;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Ensure the size is within a reasonable range for a double
    if (size < sizeof(double)) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Not enough data to bind a double
    }

    // Convert the input data to a double
    value = *((double *)data);

    // Bind the double value to the prepared statement
    rc = sqlite3_bind_double(stmt, 1, value);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Failed to bind double
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0; // Successfully executed
}