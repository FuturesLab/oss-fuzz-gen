#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

// Define a custom destructor function as a placeholder
void custom_destructor_498(void *param) {
    // Custom cleanup logic can be added here if needed
    (void)param; // To avoid unused parameter warning
}

// Custom SQLite function to provide a valid context
static void custom_sqlite_function(sqlite3_context *context, int argc, sqlite3_value **argv) {
    const void *text = sqlite3_value_blob(argv[0]);
    int text_size = sqlite3_value_bytes(argv[0]);
    sqlite3_result_text16be(context, text, text_size, custom_destructor_498);
}

int LLVMFuzzerTestOneInput_498(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *errMsg = NULL;

    // Initialize SQLite3 and create an in-memory database
    if (sqlite3_initialize() != SQLITE_OK) {
        return 0; // Initialization failed, exit early
    }

    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        sqlite3_shutdown();
        return 0; // Failed to open database, exit early
    }

    // Create a custom SQL function
    if (sqlite3_create_function(db, "custom_function_498", 1, SQLITE_UTF8, NULL, custom_sqlite_function, NULL, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        sqlite3_shutdown();
        return 0; // Failed to create custom function, exit early
    }

    // Prepare a dummy SQL statement that uses the custom function
    if (sqlite3_prepare_v2(db, "SELECT custom_function_498(?)", -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        sqlite3_shutdown();
        return 0; // Failed to prepare statement, exit early
    }

    // Bind the input data to the statement
    if (sqlite3_bind_blob(stmt, 1, data, (int)size, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        sqlite3_shutdown();
        return 0; // Failed to bind data, exit early
    }

    // Execute the statement to trigger the custom function
    sqlite3_step(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    sqlite3_shutdown();

    return 0;
}