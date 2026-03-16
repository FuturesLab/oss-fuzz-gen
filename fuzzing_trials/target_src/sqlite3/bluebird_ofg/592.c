#include <stdint.h>
#include <stddef.h> // Include for size_t
#include <stdlib.h> // Include for NULL
#include "sqlite3.h"

// Mock function to simulate aggregate function context
static void dummy_step(sqlite3_context *context, int argc, sqlite3_value **argv) {
    // Check if there is at least one argument and it's not NULL
    if (argc > 0 && argv[0] != NULL) {
        // Get the value from the first argument
        const unsigned char *value = sqlite3_value_text(argv[0]);
        if (value) {
            // Use the value in a way that affects the context
            sqlite3_result_text(context, (const char *)value, -1, SQLITE_TRANSIENT);
        }
    }
}

int LLVMFuzzerTestOneInput_592(const uint8_t *data, size_t size) {
    // Initialize SQLite
    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Create a dummy aggregate function to obtain a valid context
    sqlite3_create_function(db, "dummy_agg", 1, SQLITE_UTF8, NULL, NULL, dummy_step, NULL);

    // Prepare a statement to use the aggregate function
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT dummy_agg(?)", -1, &stmt, NULL);

    // Bind data to the statement
    if (size > 0) {
        sqlite3_bind_blob(stmt, 1, data, (int)size, SQLITE_STATIC);
    }

    // Step through the statement to trigger the aggregate function
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Obtain the context
        sqlite3_context *context = sqlite3_user_data(stmt);
        int nBytes = (size > 0) ? (int)(data[0]) : 1; // Use the first byte of data as nBytes, ensure it's at least 1

        // Call the function-under-test
        void *result = sqlite3_aggregate_context(context, nBytes);

        // Use the result in a way that prevents compiler optimizations from removing the call
        if (result != NULL) {
            volatile char *volatileResult = (volatile char *)result;
            volatileResult[0] = 0; // Access the result to prevent optimization
        }
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}