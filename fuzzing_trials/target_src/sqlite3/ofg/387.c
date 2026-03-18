#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>

// Function to initialize a SQLite statement for fuzzing
static sqlite3_stmt* initialize_sqlite_statement(sqlite3 *db) {
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value INTEGER);"
                      "INSERT INTO test (value) VALUES (?);";
    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }
    return stmt;
}

int LLVMFuzzerTestOneInput_387(const uint8_t *data, size_t size) {
    if (size < sizeof(int) * 2) {
        return 0; // Ensure there's enough data for two integers
    }

    // Initialize SQLite in-memory database
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Initialize the SQLite statement
    sqlite3_stmt *stmt = initialize_sqlite_statement(db);
    if (stmt == NULL) {
        sqlite3_close(db);
        return 0;
    }

    // Extract integers from the input data
    int index = *(int *)data; // First integer for the index
    int value = *(int *)(data + sizeof(int)); // Second integer for the value

    // Call the function under test
    sqlite3_bind_int(stmt, index, value);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}