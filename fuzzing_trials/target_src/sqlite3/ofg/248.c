#include <stdint.h>
#include <stddef.h>  // Include this for size_t
#include <sqlite3.h>

extern int LLVMFuzzerTestOneInput_248(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    sqlite3_value *val1 = NULL;  // Use NULL instead of nullptr
    sqlite3_value *val2 = NULL;  // Use NULL instead of nullptr

    // Create a SQLite memory database
    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Prepare a dummy SQL statement to create sqlite3_value objects
    sqlite3_stmt *stmt;
    const char *sql = "SELECT ?1, ?2";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    // Bind the input data to the first parameter of the SQL statement
    if (size > 0) {
        sqlite3_bind_blob(stmt, 1, data, size, SQLITE_TRANSIENT);
    } else {
        sqlite3_bind_null(stmt, 1);
    }

    // Execute the statement to initialize sqlite3_value objects
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        val1 = (sqlite3_value *)sqlite3_column_value(stmt, 0);
        val2 = (sqlite3_value *)sqlite3_column_value(stmt, 1);
    }

    // Call the function-under-test
    int result = sqlite3_vtab_in_first(val1, &val2);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}