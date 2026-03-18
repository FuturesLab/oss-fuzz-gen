#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_310(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, data BLOB);"
                      "INSERT INTO test (data) VALUES (?);";

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Execute the SQL to create the table
    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, data BLOB);", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, "INSERT INTO test (data) VALUES (?);", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Use the data as the blob to bind
    const void *blob = (const void *)data;
    int blob_size = (int)size;

    // Define a destructor for the blob, using SQLITE_TRANSIENT to make SQLite copy the data
    // Cast SQLITE_TRANSIENT to a function pointer
    rc = sqlite3_bind_blob(stmt, 1, blob, blob_size, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Prepare a simple select statement to exercise the database
    rc = sqlite3_prepare_v2(db, "SELECT * FROM test;", -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            // Access the data to ensure the row is processed
            const void *retrieved_blob = sqlite3_column_blob(stmt, 1);
            int retrieved_blob_size = sqlite3_column_bytes(stmt, 1);
            (void)retrieved_blob; // Use the retrieved_blob to avoid unused variable warning
            (void)retrieved_blob_size;
        }
    }

    // Finalize the select statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}