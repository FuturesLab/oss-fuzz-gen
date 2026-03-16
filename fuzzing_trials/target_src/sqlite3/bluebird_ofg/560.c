#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

// Assuming that the SQLite library is properly linked

int LLVMFuzzerTestOneInput_560(const uint8_t *data, size_t size) {
    // Initialize SQLite database in memory
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    if (size == 0) {
        return 0;
    }

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        return 0;
    }

    // Create a table using the input data as part of the SQL statement
    char sql[256];
    snprintf(sql, sizeof(sql), "CREATE TABLE IF NOT EXISTS fuzz_table(data TEXT);");

    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_close with sqlite3_system_errno
        sqlite3_system_errno(db);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        return 0;
    }

    // Insert data into the table
    snprintf(sql, sizeof(sql), "INSERT INTO fuzz_table (data) VALUES (?);");
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, (const char*)data, size, SQLITE_TRANSIENT);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    // Execute a simple query
    snprintf(sql, sizeof(sql), "SELECT * FROM fuzz_table;");
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}