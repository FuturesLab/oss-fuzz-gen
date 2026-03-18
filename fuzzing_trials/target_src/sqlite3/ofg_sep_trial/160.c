#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_160(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_blob *blob = NULL;
    const char *zDb = "main";
    const char *zTable = "test_table";
    const char *zColumn = "test_column";
    sqlite_int64 rowid = 1;
    int flags = 0;
    int rc;

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a test table
    const char *createTableSQL = "CREATE TABLE test_table (id INTEGER PRIMARY KEY, test_column BLOB)";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Insert a test row
    const char *insertSQL = "INSERT INTO test_table (test_column) VALUES (zeroblob(10))";
    rc = sqlite3_exec(db, insertSQL, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Attempt to open a blob
    rc = sqlite3_blob_open(db, zDb, zTable, zColumn, rowid, flags, &blob);
    if (rc == SQLITE_OK && blob != NULL) {
        // Do something with the blob, for example, read data
        char buffer[10];
        sqlite3_blob_read(blob, buffer, sizeof(buffer), 0);

        // Close the blob
        sqlite3_blob_close(blob);
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}