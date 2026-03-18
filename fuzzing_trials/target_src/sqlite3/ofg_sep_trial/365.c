#include <stdint.h>
#include <string.h>
#include <sqlite3.h>

// Fuzzing harness for sqlite3_value_int
int LLVMFuzzerTestOneInput_365(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a sqlite3_value
    if (size < sizeof(int)) {
        return 0;
    }

    // Create a sqlite3_value from the data
    sqlite3_value *value;
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *tail;
    
    // Open an in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Prepare a dummy statement
    if (sqlite3_prepare_v2(db, "SELECT ?;", -1, &stmt, &tail) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the data as an integer to the statement
    int intValue;
    memcpy(&intValue, data, sizeof(int));
    sqlite3_bind_int(stmt, 1, intValue);

    // Retrieve the value
    value = sqlite3_column_value(stmt, 0);

    // Call the function-under-test
    int result = sqlite3_value_int(value);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}