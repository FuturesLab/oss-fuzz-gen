#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <stdlib.h>  // Include for NULL
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_387(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value INTEGER); INSERT INTO test (value) VALUES (?);";

    // Open an in-memory SQLite database
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

    // Ensure we have enough data to bind
    if (size < sizeof(int)) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Extract an integer from the input data
    int value = *((int*)data);

    // Bind the integer to the SQL statement
    sqlite3_bind_int(stmt, 1, value);

    // Execute the SQL statement
    sqlite3_step(stmt);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}