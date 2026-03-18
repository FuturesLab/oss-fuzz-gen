#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

// Dummy destructor_3 function to satisfy the function signature
void dummy_destructor_3(void *data) {
    // Do nothing
}

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
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

    // Bind the blob to the SQL statement
    rc = sqlite3_bind_blob64(stmt, 1, (const void *)data, (sqlite3_uint64)size, dummy_destructor_3);

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Close the database
    sqlite3_close(db);

    return 0;
}