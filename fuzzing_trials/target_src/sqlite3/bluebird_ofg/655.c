#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include this for memcpy
#include <stdlib.h>  // Include this for malloc and free
#include "sqlite3.h"

// User-defined function that uses sqlite3_result_double
void my_double_function(sqlite3_context *context, int argc, sqlite3_value **argv) {
    if (argc == 1 && sqlite3_value_type(argv[0]) == SQLITE_FLOAT) {
        double value = sqlite3_value_double(argv[0]);
        sqlite3_result_double(context, value);
    } else {
        sqlite3_result_null(context);
    }
}

int LLVMFuzzerTestOneInput_655(const uint8_t *data, size_t size) {
    // Ensure the data size is at least the size of a double
    if (size < sizeof(double)) {
        return 0;
    }

    // Cast the first part of the data to a double
    double value;
    memcpy(&value, data, sizeof(double));

    // Initialize SQLite in-memory database
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Register the user-defined function
    if (sqlite3_create_function(db, "my_double_function", 1, SQLITE_UTF8, NULL, my_double_function, NULL, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement that uses the user-defined function
    sqlite3_stmt *stmt;
    const char *sql = "SELECT my_double_function(?)";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the double value to the statement
    if (sqlite3_bind_double(stmt, 1, value) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Step the statement
    if (sqlite3_step(stmt) != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}