#include <stdint.h>
#include <stddef.h>  // Include this for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_399(const uint8_t *data, size_t size) {
    // Initialize SQLite
    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Prepare a dummy SQL statement to create a sqlite3_value
    sqlite3_stmt *stmt;
    const char *sql = "SELECT ?";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    // Bind the input data to the SQL statement parameter
    if (size > 0) {
        sqlite3_bind_blob(stmt, 1, data, size, SQLITE_TRANSIENT);
    } else {
        sqlite3_bind_null(stmt, 1);
    }

    // Execute the statement to obtain the sqlite3_value
    sqlite3_step(stmt);

    // Get the sqlite3_value
    sqlite3_value *value = sqlite3_column_value(stmt, 0);

    // Call the function-under-test
    int numericType = sqlite3_value_numeric_type(value);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}