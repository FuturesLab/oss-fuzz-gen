#include <stdint.h>
#include <sqlite3.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_372(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value REAL);"
                      "INSERT INTO test (value) VALUES (?);";

    // Open a new in-memory SQLite database
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

    // Ensure we have enough data to extract an integer and a double
    if (size < sizeof(int) + sizeof(double)) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Extract an integer and a double from the input data
    int index = *((int *)data);
    double value = *((double *)(data + sizeof(int)));

    // Bind the double value to the prepared statement
    sqlite3_bind_double(stmt, index, value);

    // Finalize and close
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}