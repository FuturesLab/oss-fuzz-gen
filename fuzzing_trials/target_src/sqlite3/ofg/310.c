#include <stdint.h>
#include <sqlite3.h>
#include <assert.h>
#include <string.h>

// Function to create a simple SQLite statement for testing
sqlite3_stmt* create_test_stmt(sqlite3 *db) {
    const char *sql = "CREATE TABLE test (id INTEGER, name TEXT);"
                      "INSERT INTO test (id, name) VALUES (1, 'Alice');"
                      "SELECT * FROM test;";
    sqlite3_stmt *stmt = NULL;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    assert(rc == SQLITE_OK);
    return stmt;
}

int LLVMFuzzerTestOneInput_310(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    int column_index;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    assert(rc == SQLITE_OK);

    // Create a test statement
    stmt = create_test_stmt(db);

    // Ensure the statement is valid
    if (stmt == NULL) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement to ensure the table and data are set up
    rc = sqlite3_step(stmt);
    while (rc == SQLITE_ROW || rc == SQLITE_DONE) {
        rc = sqlite3_step(stmt);
    }
    sqlite3_reset(stmt);

    // Use the data to determine the column index
    if (size > 0) {
        column_index = data[0] % 2;  // Assuming we have 2 columns in the test table
    } else {
        column_index = 0;
    }

    // Call the function-under-test
    rc = sqlite3_step(stmt); // Move to the first row of the result set
    if (rc == SQLITE_ROW) {
        const void *column_name = sqlite3_column_name16(stmt, column_index);

        // Check that the column name is not NULL
        if (column_name != NULL) {
            // Do something with the column name if needed
            (void)column_name;  // Suppress unused variable warning
        }
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}