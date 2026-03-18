#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_160(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    const char *db_name = "main"; // Use "main" for in-memory database
    const char *table_name = "test_table";
    const char *column_name = "test_column";
    sqlite_int64 row_id = 1;
    int flags = 0;
    sqlite3_blob *blob = NULL;
    int rc;

    // Open an in-memory database for testing purposes
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a sample table
    const char *create_table_sql = "CREATE TABLE test_table (id INTEGER PRIMARY KEY, test_column BLOB);";
    rc = sqlite3_exec(db, create_table_sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Insert a sample row
    const char *insert_sql = "INSERT INTO test_table (id, test_column) VALUES (1, zeroblob(10));";
    rc = sqlite3_exec(db, insert_sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    rc = sqlite3_blob_open(db, db_name, table_name, column_name, row_id, flags, &blob);

    // If blob is opened successfully, write fuzzing data to it
    if (rc == SQLITE_OK && blob != NULL && size > 0) {
        // Write the fuzzing data to the blob
        size_t write_size = size < 10 ? size : 10; // Ensure we do not exceed the blob size
        sqlite3_blob_write(blob, data, write_size, 0);
    }

    // Clean up
    if (blob != NULL) {
        sqlite3_blob_close(blob);
    }
    sqlite3_close(db);

    return 0;
}