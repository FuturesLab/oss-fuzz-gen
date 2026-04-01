#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

// Define a simple SQL statement for testing
#define SQL_STATEMENT "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value TEXT); INSERT INTO test (value) VALUES ('test');"

int LLVMFuzzerTestOneInput_317(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc;
    char *errMsg = NULL;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Execute the SQL statement to set up the database
    rc = sqlite3_exec(db, SQL_STATEMENT, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement from the input data
    rc = sqlite3_prepare_v2(db, (const char *)data, size, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    sqlite3_step(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}