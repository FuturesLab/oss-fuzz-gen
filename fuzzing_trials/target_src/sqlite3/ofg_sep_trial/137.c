#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
    // Initialize an SQLite memory database
    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Prepare a dummy SQL statement to obtain an sqlite3_value object
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT ?", -1, &stmt, NULL);

    // Bind the input data to the SQL statement as a blob
    sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC);

    // Execute the statement to move to the first row
    sqlite3_step(stmt);

    // Obtain the sqlite3_value object from the statement
    const sqlite3_value *value = sqlite3_column_value(stmt, 0);

    // Call the function-under-test
    int bytes = sqlite3_value_bytes((sqlite3_value *)value);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}