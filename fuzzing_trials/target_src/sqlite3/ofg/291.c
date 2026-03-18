#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_291(const uint8_t *data, size_t size) {
    // Initialize SQLite3 library
    if (sqlite3_initialize() != SQLITE_OK) {
        return 0;
    }

    // Open a new in-memory SQLite database
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        sqlite3_shutdown();
        return 0;
    }

    // Prepare an SQL statement
    sqlite3_stmt *stmt;
    const char *sql = "CREATE TABLE test (data BLOB);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        sqlite3_shutdown();
        return 0;
    }

    // Execute the SQL statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        sqlite3_shutdown();
        return 0;
    }
    sqlite3_finalize(stmt);

    // Insert the input data as a blob into the table
    sql = "INSERT INTO test (data) VALUES (?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        sqlite3_shutdown();
        return 0;
    }
    sqlite3_bind_blob(stmt, 1, data, size, SQLITE_TRANSIENT);

    // Execute the insert statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        sqlite3_shutdown();
        return 0;
    }
    sqlite3_finalize(stmt);

    // Clean up
    sqlite3_close(db);
    sqlite3_shutdown();

    return 0;
}