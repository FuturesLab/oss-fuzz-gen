#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_305(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_blob *blob;
    int result;
    const char *db_name = "test.db";
    const char *table_name = "test_table";
    const char *column_name = "data";
    int row_id = 1;
    const void *blob_data;
    int blob_size;
    int offset;

    // Initialize SQLite database in memory
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Create a table for testing
    const char *create_table_sql = "CREATE TABLE test_table (id INTEGER PRIMARY KEY, data BLOB)";
    if (sqlite3_exec(db, create_table_sql, 0, 0, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Insert a row into the table
    const char *insert_sql = "INSERT INTO test_table (id, data) VALUES (1, zeroblob(10))";
    if (sqlite3_exec(db, insert_sql, 0, 0, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Open a blob for writing
    if (sqlite3_blob_open(db, db_name, table_name, column_name, row_id, 1, &blob) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare data for writing
    blob_data = (const void *)data;
    blob_size = (size > 10) ? 10 : size; // Limit size to 10 for this example
    offset = 0;

    // Call the function-under-test
    result = sqlite3_blob_write(blob, blob_data, blob_size, offset);

    // Clean up
    sqlite3_blob_close(blob);
    sqlite3_close(db);

    return 0;
}