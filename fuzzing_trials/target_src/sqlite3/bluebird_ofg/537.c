#include <stdint.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_537(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc;

    // Initialize SQLite in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare a dummy SQL statement
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare an INSERT statement
    sql = "INSERT INTO test (value) VALUES (?);";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the fuzzing data to the statement
    if (size > 0) {
        sqlite3_bind_text(stmt, 1, (const char *)data, size, SQLITE_TRANSIENT);
    }

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Reset the statement to use it again
    sqlite3_reset(stmt);

    // Call the function-under-test
    int data_count = sqlite3_data_count(stmt);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}