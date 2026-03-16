#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"

// Define a dummy destructor function for the text result
void dummy_destructor_469(void *ptr) {
    // Do nothing, just a placeholder
}

// Custom SQLite function to be used for obtaining a valid sqlite3_context
void custom_function_469(sqlite3_context *context, int argc, sqlite3_value **argv) {
    // Use the context to set a result with the provided data
    if (argc > 0) {
        const void *data = sqlite3_value_blob(argv[0]);
        int size = sqlite3_value_bytes(argv[0]);
        sqlite3_result_text16be(context, data, size, dummy_destructor_469);
    }
}

int LLVMFuzzerTestOneInput_469(const uint8_t *data, size_t size) {
    // Ensure that the data is not NULL and size is non-zero
    if (data == NULL || size == 0) {
        return 0;
    }

    // Create a valid SQLite database connection
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Register the custom function
    rc = sqlite3_create_function(db, "custom_function_469", 1, SQLITE_UTF8, NULL, custom_function_469, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a SQL statement that calls the custom function
    rc = sqlite3_prepare_v2(db, "SELECT custom_function_469(?)", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data to the SQL statement
    rc = sqlite3_bind_blob(stmt, 1, data, (int)size, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement
    rc = sqlite3_step(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}