#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_397(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    char *errMsg = NULL;
    int rc;

    // Initialize an SQLite memory context
    if (sqlite3_initialize() != SQLITE_OK) {
        return 0;
    }

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        sqlite3_shutdown();
        return 0;
    }

    // Create a dummy table
    rc = sqlite3_exec(db, "CREATE TABLE test (data TEXT);", 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        sqlite3_shutdown();
        return 0;
    }

    // Prepare an insert statement
    rc = sqlite3_prepare_v2(db, "INSERT INTO test (data) VALUES (?);", -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        sqlite3_shutdown();
        return 0;
    }

    // Bind the input data as a text value
    sqlite3_bind_text(stmt, 1, (const char*)data, size, SQLITE_TRANSIENT);

    // Execute the statement
    sqlite3_step(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    sqlite3_shutdown();

    return 0;
}