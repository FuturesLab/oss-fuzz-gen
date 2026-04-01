#include <stdint.h>
#include <stddef.h>  // Include this for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "CREATE TABLE test(id INT); INSERT INTO test (id) VALUES (1);";

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

    // Prepare a statement from the fuzzing data
    const char *tail;
    rc = sqlite3_prepare_v2(db, (const char *)data, size, &stmt, &tail);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    int busy = sqlite3_stmt_busy(stmt);

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Close the database
    sqlite3_close(db);

    return 0;
}