#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_371(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    char *errMsg = 0;

    // Initialize SQLite in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a dummy table
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value BLOB)";
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare a dummy insert statement
    const char *insertSQL = "INSERT INTO test (value) VALUES (?)";
    rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Use the first byte of data as the index and the next two bytes as the size
    int index = (size > 0) ? data[0] % 10 : 0; // Limiting index to 0-9
    int zeroblobSize = (size > 2) ? ((data[1] << 8) | data[2]) : 0;

    // Call the function-under-test
    sqlite3_bind_zeroblob(stmt, index, zeroblobSize);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}