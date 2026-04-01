#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

// Fuzzer entry point
int LLVMFuzzerTestOneInput_217(const uint8_t *data, size_t size) {
    // Initialize an SQLite database in memory
    sqlite3 *db;
    char *errMsg = 0;

    if (sqlite3_open(":memory:", &db)) {
        sqlite3_close(db);
        return 0;
    }

    // Create a table
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value BLOB);";
    if (sqlite3_exec(db, createTableSQL, 0, 0, &errMsg) != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare an SQL statement
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO test (value) VALUES (?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data to the SQL statement
    if (sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the SQL statement
    sqlite3_step(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    // Return 0 to indicate the fuzzer's execution is complete
    return 0;
}