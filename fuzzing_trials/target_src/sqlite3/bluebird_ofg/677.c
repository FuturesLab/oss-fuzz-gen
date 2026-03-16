#include <stdint.h>
#include "sqlite3.h"
#include <string.h>

// Function to prepare a simple SQL statement for testing
static sqlite3_stmt* prepare_test_statement(sqlite3 *db) {
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER, data BLOB);"
                      "INSERT INTO test (id, data) VALUES (1, ?);"
                      "SELECT data FROM test WHERE id = 1;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return NULL;
    }
    return stmt;
}

int LLVMFuzzerTestOneInput_677(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt = NULL;
    int rc;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare the test statement
    stmt = prepare_test_statement(db);
    if (stmt == NULL) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data as a BLOB to the statement
    sqlite3_bind_blob(stmt, 1, data, (int)size, SQLITE_STATIC);

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Call the function-under-test
        const void *blob_data = sqlite3_column_blob(stmt, 0);
        // Use blob_data for further testing if needed
        (void)blob_data; // Suppress unused variable warning
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}