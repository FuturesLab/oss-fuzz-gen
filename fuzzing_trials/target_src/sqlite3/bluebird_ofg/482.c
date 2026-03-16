#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <string.h>  // Include for NULL
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_482(const uint8_t *data, size_t size) {
    // Initialize SQLite
    if (sqlite3_initialize() != SQLITE_OK) {
        return 0;
    }

    // Initialize variables
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    uint64_t n = 0;

    // Open a temporary in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        sqlite3_shutdown();
        return 0;
    }

    // Ensure size is sufficient to extract a uint64_t value
    if (size < sizeof(uint64_t)) {
        sqlite3_close(db);
        sqlite3_shutdown();
        return 0;
    }

    // Use the first 8 bytes of data to set the value of n
    n = *((uint64_t*)data);

    // Prepare a dummy statement to test sqlite3_result_zeroblob64
    if (sqlite3_prepare_v2(db, "SELECT zeroblob(?)", -1, &stmt, NULL) == SQLITE_OK) {
        // Bind the zeroblob size
        sqlite3_bind_int64(stmt, 1, n);

        // Execute the statement
        sqlite3_step(stmt);
    }

    // Cleanup
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    sqlite3_shutdown();

    return 0;
}