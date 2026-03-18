#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_203(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_blob *blob;
    int rc;
    const char *db_filename = "test.db";
    const char *table_name = "test_table";
    const char *column_name = "test_column";
    int row_id = 1;
    void *buffer;
    int buffer_size;

    // Initialize SQLite database
    rc = sqlite3_open(db_filename, &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a sample table and insert a row if not exists
    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS test_table (id INTEGER PRIMARY KEY, test_column BLOB);";
    sqlite3_exec(db, create_table_sql, 0, 0, 0);

    const char *insert_sql = "INSERT OR IGNORE INTO test_table (id, test_column) VALUES (1, zeroblob(100));";
    sqlite3_exec(db, insert_sql, 0, 0, 0);

    // Open a blob handle
    rc = sqlite3_blob_open(db, "main", table_name, column_name, row_id, 0, &blob);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a buffer for reading
    buffer_size = size < 100 ? size : 100; // Limit buffer size to 100 for this example
    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        sqlite3_blob_close(blob);
        sqlite3_close(db);
        return 0;
    }

    // Copy data to buffer
    memcpy(buffer, data, buffer_size);

    // Call the function-under-test
    sqlite3_blob_read(blob, buffer, buffer_size, 0);

    // Clean up
    free(buffer);
    sqlite3_blob_close(blob);
    sqlite3_close(db);

    return 0;
}