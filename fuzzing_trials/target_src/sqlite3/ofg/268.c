#include <stdint.h>
#include <stddef.h>  // Include this for size_t
#include <sqlite3.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_268(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER, value REAL);"
                      "INSERT INTO test (id, value) VALUES (1, 1.23);"
                      "SELECT value FROM test WHERE id = 1;";

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Execute the SQL statement
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, "SELECT value FROM test WHERE id = 1;", -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Fuzzing target: Call sqlite3_column_double
        double value = sqlite3_column_double(stmt, 0);
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

#ifdef __cplusplus
}
#endif