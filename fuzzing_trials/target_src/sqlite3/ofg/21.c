#include <stdint.h>
#include <stddef.h> // Include for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int blobSize;

    // Ensure the size is large enough to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    blobSize = *((int *)data);

    // Open an in-memory database to create a valid context
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Prepare a statement to create a valid sqlite3_context
    if (sqlite3_prepare_v2(db, "SELECT zeroblob(?)", -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the blob size to the statement
    if (sqlite3_bind_int(stmt, 1, blobSize) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement to invoke the function under test
    sqlite3_step(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}