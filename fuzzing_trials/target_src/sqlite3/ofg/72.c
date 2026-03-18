#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, blob BLOB); INSERT INTO test (blob) VALUES (?);";

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

    // Ensure size is not zero to avoid binding a zero-length blob
    if (size == 0) {
        size = 1;
    }

    // Bind a zeroblob of size 'size' to the first parameter of the statement
    sqlite3_uint64 zeroblob_size = (sqlite3_uint64)size;
    rc = sqlite3_bind_zeroblob64(stmt, 1, zeroblob_size);

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Close the database
    sqlite3_close(db);

    return 0;
}