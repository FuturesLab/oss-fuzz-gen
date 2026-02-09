#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_320(const uint8_t *data, size_t size) {
    sqlite3_stmt *stmt = NULL;
    int rc;
    int index = 1; // SQLite bind index starts at 1
    sqlite3_uint64 blob_size = (sqlite3_uint64)size; // Size of the blob to bind

    // Create a new SQLite database in memory
    sqlite3 *db;
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table for testing
    const char *create_table_sql = "CREATE TABLE test_table (id INTEGER PRIMARY KEY, data BLOB);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Prepare an insert statement
    const char *insert_sql = "INSERT INTO test_table (data) VALUES (?);";
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Bind the blob data to the statement
    rc = sqlite3_bind_blob64(stmt, index, data, blob_size, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Binding failed
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}