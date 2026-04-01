#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_300(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    sqlite3_blob *blob;
    int rc;
    
    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a table and insert a blob
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, data BLOB)";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    const char *insert_sql = "INSERT INTO test (data) VALUES (zeroblob(10))";
    rc = sqlite3_exec(db, insert_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Open a blob handle
    rc = sqlite3_blob_open(db, "main", "test", "data", 1, 1, &blob);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare data to write
    int write_size = size < 10 ? size : 10; // Ensure we do not exceed the blob size
    const void *write_data = (const void *)data;
    int offset = 0;

    // Call the function-under-test
    sqlite3_blob_write(blob, write_data, write_size, offset);

    // Clean up
    sqlite3_blob_close(blob);
    sqlite3_close(db);

    return 0;
}