#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_182(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    char *errMsg = 0;
    char *sql = "CREATE TABLE IF NOT EXISTS test(id INT, value TEXT); INSERT INTO test (id, value) VALUES (?, ?);";

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Execute SQL to create table
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind data to the statement
    if (size > 0) {
        sqlite3_bind_int(stmt, 1, data[0]);
    }
    if (size > 1) {
        sqlite3_bind_text(stmt, 2, (const char *)(data + 1), size - 1, SQLITE_TRANSIENT);
    }

    // Call the function-under-test
    sqlite3_clear_bindings(stmt);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}