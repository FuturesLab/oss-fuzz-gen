#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_396(const uint8_t *data, size_t size) {
    // Initialize SQLite
    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Prepare a SQL statement to use the input data
    sqlite3_stmt *stmt;
    const char *sql = "SELECT ?"; // Use parameterized query
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    // Bind the input data as a blob to the SQL statement
    sqlite3_bind_blob(stmt, 1, data, size, SQLITE_TRANSIENT);

    // Execute the statement
    sqlite3_step(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}