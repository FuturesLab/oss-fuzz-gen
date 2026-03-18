#include <stdint.h>
#include <stddef.h> // Include for size_t
#include <stdlib.h> // Include for NULL
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    // Check if input data is valid
    if (data == NULL || size == 0) {
        return 0;
    }

    // Declare and initialize a sqlite3_value object
    sqlite3_value *value;
    sqlite3 *db;
    sqlite3_stmt *stmt;

    // Initialize a database connection
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Prepare a statement with a more complex query to better utilize the input data
    const char *sql = "CREATE TABLE test (data BLOB); INSERT INTO test (data) VALUES (?); SELECT data FROM test;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data to the statement
    if (sqlite3_bind_blob(stmt, 1, data, size, SQLITE_TRANSIENT) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement to insert the data
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Reset the statement to select the data
    sqlite3_reset(stmt);

    // Step through the statement to initialize the value
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        value = sqlite3_column_value(stmt, 0);
    } else {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    int result = sqlite3_value_type(value);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return result;
}