#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <stdlib.h>  // Include for NULL
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_373(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER, value REAL); INSERT INTO test (id, value) VALUES (?, ?);";

    // Initialize SQLite database in memory
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

    // Ensure there is enough data to read an integer and a double
    if (size < sizeof(int) + sizeof(double)) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Extract an integer from the data
    int index = *(int *)data;
    data += sizeof(int);
    size -= sizeof(int);

    // Extract a double from the remaining data
    double value = *(double *)data;

    // Call the function-under-test
    sqlite3_bind_double(stmt, index, value);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}