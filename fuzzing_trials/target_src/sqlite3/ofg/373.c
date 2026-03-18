#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_373(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "SELECT ?";

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

    // Ensure there is enough data to extract an integer and a double
    if (size < sizeof(int) + sizeof(double)) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Extract an integer and a double from the input data
    int index = *((int *)data);
    double value = *((double *)(data + sizeof(int)));

    // Call the function-under-test
    sqlite3_bind_double(stmt, index, value);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}