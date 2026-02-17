#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <limits.h> // Include limits.h for INT_MAX

int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    int n;

    // Open a new database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Ensure database opened successfully
    }

    // Prepare a simple SQL statement
    rc = sqlite3_prepare_v2(db, "SELECT ?", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Ensure statement prepared successfully
    }

    // Ensure size is within a reasonable range for the second parameter
    if (size < 0) {
        n = 0; // Use 0 if size is negative
    } else if (size > INT_MAX) {
        n = INT_MAX; // Limit to INT_MAX to avoid overflow
    } else {
        n = (int)size; // Cast size to int
    }

    // Bind the blob data to the statement
    sqlite3_bind_zeroblob(stmt, 1, n);

    // Execute the statement
    sqlite3_step(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}