#include <stdint.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_522(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create an SQLite memory context
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Prepare an SQLite statement to create a value
    sqlite3_stmt *stmt;
    const char *sql = "SELECT ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data to the statement as a blob
    if (sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement to get a value
    if (sqlite3_step(stmt) != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Get the value from the statement
    const sqlite3_value *original_value = sqlite3_column_value(stmt, 0);

    // Check if the original_value is NULL and handle it
    if (original_value == NULL) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    sqlite3_value *duplicated_value = sqlite3_value_dup(original_value);

    // Check if the duplicated_value is NULL and handle it
    if (duplicated_value != NULL) {
        // Use the duplicated value in some way to ensure it's not optimized out
        int value_type = sqlite3_value_type(duplicated_value);

        // Additional use of the duplicated_value to ensure coverage
        if (value_type == SQLITE_BLOB) {
            const void *blob_data = sqlite3_value_blob(duplicated_value);
            int blob_size = sqlite3_value_bytes(duplicated_value);
            if (blob_data != NULL && blob_size > 0) {
                // Simulate some operation on the blob data
                volatile int dummy = 0;
                for (int i = 0; i < blob_size; i++) {
                    dummy += ((const uint8_t *)blob_data)[i];
                }
            }
        }

        // Clean up
        sqlite3_value_free(duplicated_value);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}