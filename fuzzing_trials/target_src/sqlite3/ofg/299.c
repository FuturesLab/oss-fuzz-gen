#include <stdint.h>
#include <stddef.h> // Include this for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_299(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_blob *blob;
    int rc;
    const char *db_name = "test.db";
    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, data BLOB);";
    const char *sql_insert_blob = "INSERT INTO test (data) VALUES (zeroblob(1024));";
    const char *blob_table = "test";
    const char *blob_column = "data";
    int row_id = 1;
    int blob_size = 1024;
    int offset = 0;

    // Open database connection
    rc = sqlite3_open(db_name, &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create table if not exists
    rc = sqlite3_exec(db, sql_create_table, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Insert a blob
    rc = sqlite3_exec(db, sql_insert_blob, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Open blob
    rc = sqlite3_blob_open(db, "main", blob_table, blob_column, row_id, 1, &blob);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Write data to blob
    if (size > 0) {
        rc = sqlite3_blob_write(blob, data, (int)size, offset);
    }

    // Close blob
    sqlite3_blob_close(blob);

    // Close database connection
    sqlite3_close(db);

    return 0;
}