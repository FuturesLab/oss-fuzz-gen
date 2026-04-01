#include <stdint.h>
#include <stddef.h> // Include for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_361(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    uint64_t n = 0;

    // Ensure the size is large enough to extract a uint64_t value
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Extract a uint64_t value from the input data
    n = *(const uint64_t *)data;

    // Open an in-memory SQLite database
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Create a zeroblob of size n in the database
    sqlite3_stmt *stmt;
    const char *sql = "SELECT zeroblob(?)";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int64(stmt, 1, n);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}