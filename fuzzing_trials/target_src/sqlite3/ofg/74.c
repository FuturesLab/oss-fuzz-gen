#include <stdint.h>
#include <stddef.h>  // For size_t
#include <string.h>  // For NULL
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, data BLOB); INSERT INTO test (data) VALUES (?);";

    // Open a new in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Ensure the data size is not zero and within a reasonable range
    if (size > 0 && size <= sizeof(sqlite3_uint64)) {
        // Use the first byte of data to determine the index for binding
        int index = data[0] % 2 + 1; // Bind to the first or second parameter

        // Use the remaining bytes as a sqlite3_uint64 value
        sqlite3_uint64 zeroblob_size = 0;
        for (size_t i = 1; i < size && i <= sizeof(sqlite3_uint64); ++i) {
            zeroblob_size = (zeroblob_size << 8) | data[i];
        }

        // Call the function-under-test
        sqlite3_bind_zeroblob64(stmt, index, zeroblob_size);
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}