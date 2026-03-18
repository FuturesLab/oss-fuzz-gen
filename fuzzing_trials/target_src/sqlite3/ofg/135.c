#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

// Dummy callback function to match the expected function pointer type
void dummy_callback_135() {}

// Fuzzing entry point
int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    char *errMsg = 0;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, data TEXT);";

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Execute SQL to create a table
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a SQL statement
    sql = "INSERT INTO test (data) VALUES (?);";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Use the first byte of data as the index for binding
    int index = size > 0 ? data[0] % 10 : 0;

    // Bind a pointer to the statement
    sqlite3_bind_pointer(stmt, index, (void *)data, "test_pointer", (void (*)(void *))dummy_callback_135);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}