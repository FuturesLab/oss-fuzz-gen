#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_363(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    // Initialize SQLite in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Early exit if database cannot be opened
    }

    // Create a dummy table
    rc = sqlite3_exec(db, "CREATE TABLE test (data TEXT);", 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0; // Early exit if table cannot be created
    }

    // Prepare an SQL statement
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, "INSERT INTO test (data) VALUES (?);", -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Early exit if statement cannot be prepared
    }

    // Bind the input data to the SQL statement
    rc = sqlite3_bind_text(stmt, 1, (const char *)data, size, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Early exit if data cannot be bound
    }

    // Execute the SQL statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Early exit if statement execution fails
    }

    // Cleanup
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}