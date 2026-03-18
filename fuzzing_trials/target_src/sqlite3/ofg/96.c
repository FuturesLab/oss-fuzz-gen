#include <stdint.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    if (size < sizeof(double)) {
        return 0;
    }

    // Initialize SQLite3 context and value
    sqlite3 *db;
    sqlite3_open(":memory:", &db);
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT ?", -1, &stmt, NULL);

    // Bind the input data as a double to the statement
    double input_double;
    memcpy(&input_double, data, sizeof(double));
    sqlite3_bind_double(stmt, 1, input_double);

    // Execute the statement and get the result
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        double result = sqlite3_column_double(stmt, 0);
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}