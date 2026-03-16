#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_295(const uint8_t *data, size_t size) {
    // Initialize SQLite
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Create a simple table
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    if (sqlite3_exec(db, createTableSQL, 0, 0, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement
    sqlite3_stmt *stmt;
    const char *insertSQL = "INSERT INTO test (value) VALUES (?);";
    if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data to the statement
    int index = 1; // Binding to the first parameter
    if (sqlite3_bind_text(stmt, index, (const char *)data, size, SQLITE_TRANSIENT) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement
    sqlite3_step(stmt);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}