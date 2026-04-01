#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>

// Function signature for the function to be fuzzed
const void *sqlite3_column_blob(sqlite3_stmt *, int);

int LLVMFuzzerTestOneInput_197(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, blob_data BLOB);"
                      "INSERT INTO test (blob_data) VALUES (?);";

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data as a blob to the SQL statement
    rc = sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the SQL statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Reset the statement to query the inserted data
    sqlite3_reset(stmt);

    // Prepare a SELECT statement to retrieve the blob data
    const char *select_sql = "SELECT blob_data FROM test WHERE id = 1;";
    rc = sqlite3_prepare_v2(db, select_sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the SELECT statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Call the function-under-test
        const void *blob = sqlite3_column_blob(stmt, 0);
        (void)blob; // Use blob to avoid unused variable warning
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}