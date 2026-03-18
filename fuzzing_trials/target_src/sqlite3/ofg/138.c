#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

// Function prototype for internal SQLite function
int sqlite3_value_bytes(sqlite3_value*);

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    // Ensure the data is not NULL and has a size greater than 0
    if (data == NULL || size == 0) {
        return 0;
    }

    // Create a new SQLite memory value
    sqlite3_value *value;
    sqlite3 *db;
    sqlite3_stmt *stmt;

    // Open a temporary SQLite database in memory
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Prepare a dummy SQL statement
    if (sqlite3_prepare_v2(db, "SELECT ?", -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data to the SQL statement
    sqlite3_bind_text(stmt, 1, (const char *)data, (int)size, SQLITE_TRANSIENT);

    // Retrieve the bound value
    value = sqlite3_column_value(stmt, 0);

    // Call the function-under-test
    int bytes = sqlite3_value_bytes(value);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}