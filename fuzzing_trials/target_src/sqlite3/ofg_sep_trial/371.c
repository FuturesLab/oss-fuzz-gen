#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_371(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    // Open a temporary in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table for testing
    const char *sql_create_table = "CREATE TABLE test (id INTEGER PRIMARY KEY, data BLOB);";
    rc = sqlite3_exec(db, sql_create_table, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare an insert statement
    const char *sql_insert = "INSERT INTO test (data) VALUES (?);";
    rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Use the first byte of data to determine the index for binding
    int index = data[0] % 10; // Keep index within a reasonable range

    // Use the remaining bytes as the size for the zeroblob
    int zeroblob_size = size - 1;

    // Call the function-under-test
    sqlite3_bind_zeroblob(stmt, index, zeroblob_size);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}