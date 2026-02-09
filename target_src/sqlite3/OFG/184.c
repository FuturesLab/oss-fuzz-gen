#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_184(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    double value;

    // Ensure that the size is appropriate to convert to a double
    if (size < sizeof(double)) {
        return 0; // Not enough data to create a double
    }

    // Open a new SQLite database in memory
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Prepare a simple SQL statement
    if (sqlite3_prepare_v2(db, "SELECT ?", -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Convert the first 8 bytes of data to a double
    value = *((double *)data);

    // Bind the double value to the first parameter of the statement
    sqlite3_bind_double(stmt, 1, value);

    // Execute the statement (this will not do much since we are not fetching results)
    sqlite3_step(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}