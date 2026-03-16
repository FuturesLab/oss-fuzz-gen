#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_649(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    double double_value = 0.0;

    // Ensure that the size is sufficient to extract a double value
    if (size < sizeof(double)) {
        return 0;
    }

    // Copy the data to the double_value
    double_value = *(double*)data;

    // Initialize a SQLite database connection
    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Prepare a dummy SQL statement to obtain a valid sqlite3_context
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT ?", -1, &stmt, NULL);

    // Bind the double value to the SQL statement
    sqlite3_bind_double(stmt, 1, double_value);

    // Execute the statement
    sqlite3_step(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}