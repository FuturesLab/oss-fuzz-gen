#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_304(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_blob *blob = NULL;
    const char *db_name = "test.db";
    const char *table_name = "test_table";
    const char *column_name = "test_column";
    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS test_table (id INTEGER PRIMARY KEY, test_column BLOB)";
    const char *sql_insert_blob = "INSERT INTO test_table (test_column) VALUES (zeroblob(100))";
    int rc;
    int offset = 0;
    int bytes_to_write = size < 100 ? size : 100; // Limit to 100 bytes for the blob

    // Open a connection to the SQLite database
    rc = sqlite3_open(db_name, &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create table if it doesn't exist
    rc = sqlite3_exec(db, sql_create_table, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Insert a blob with a fixed size
    rc = sqlite3_exec(db, sql_insert_blob, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Open the blob for writing
    rc = sqlite3_blob_open(db, "main", table_name, column_name, 1, 1, &blob);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Write data to the blob
    rc = sqlite3_blob_write(blob, data, bytes_to_write, offset);
    
    // Close the blob
    sqlite3_blob_close(blob);

    // Close the database connection
    sqlite3_close(db);

    return 0;
}