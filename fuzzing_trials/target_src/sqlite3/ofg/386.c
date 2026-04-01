#include <stdint.h>
#include <stddef.h>  // Include for size_t and NULL
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_386(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER); INSERT INTO test (id) VALUES (?);";

    // Open a new in-memory database
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

    // Extract an integer from the input data to use as a parameter
    int param_value = 0;
    if (size >= sizeof(int)) {
        param_value = *((int *)data);
    }

    // Bind the integer parameter to the SQL statement
    sqlite3_bind_int(stmt, 1, param_value);

    // Execute the SQL statement
    sqlite3_step(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}