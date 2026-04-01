#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_309(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int result;
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, data BLOB); INSERT INTO test (data) VALUES (?);";

    // Initialize SQLite in-memory database
    result = sqlite3_open(":memory:", &db);
    if (result != SQLITE_OK) {
        return 0;
    }

    // Prepare the SQL statement
    result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the blob data to the SQL statement
    if (size > 0) {
        result = sqlite3_bind_blob(stmt, 1, (const void *)data, (int)size, SQLITE_STATIC);
    } else {
        // If size is 0, bind an empty blob
        result = sqlite3_bind_blob(stmt, 1, "", 0, SQLITE_STATIC);
    }

    // Execute the SQL statement
    if (result == SQLITE_OK) {
        sqlite3_step(stmt);
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}