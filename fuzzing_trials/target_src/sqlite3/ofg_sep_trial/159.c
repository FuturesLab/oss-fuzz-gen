#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_159(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_blob *blob = NULL;
    int rc;
    const char *db_name = "main"; // Use "main" for in-memory database
    const char *table_name = "test_table";
    const char *column_name = "test_column";
    sqlite_int64 rowid = 1;
    int flags = 1; // Use flags = 1 to open blob for writing

    // Initialize SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a test table
    rc = sqlite3_exec(db, "CREATE TABLE test_table (id INTEGER PRIMARY KEY, test_column BLOB);", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Insert a test row
    rc = sqlite3_exec(db, "INSERT INTO test_table (id, test_column) VALUES (1, zeroblob(10));", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    rc = sqlite3_blob_open(db, db_name, table_name, column_name, rowid, flags, &blob);

    // If blob is opened successfully, write data to it
    if (rc == SQLITE_OK && blob != NULL && size > 0) {
        size_t write_size = size < 10 ? size : 10; // Write up to 10 bytes
        sqlite3_blob_write(blob, data, write_size, 0);
    }

    // Clean up
    if (blob != NULL) {
        sqlite3_blob_close(blob);
    }
    sqlite3_close(db);

    return 0;
}