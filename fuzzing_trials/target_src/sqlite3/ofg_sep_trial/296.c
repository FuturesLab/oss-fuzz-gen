#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_296(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int index = 1; // Typically, binding index starts from 1
    int result;

    // Initialize SQLite in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Prepare a simple SQL statement
    const char *sql = "CREATE TABLE test (id INTEGER); INSERT INTO test (id) VALUES (?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data as text to the SQL statement
    result = sqlite3_bind_text(stmt, index, (const char *)data, size, SQLITE_TRANSIENT);

    // Execute the statement
    if (result == SQLITE_OK) {
        sqlite3_step(stmt);
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}