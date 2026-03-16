#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

// Assuming that the SQLite library is properly linked

int LLVMFuzzerTestOneInput_659(const uint8_t *data, size_t size) {
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
        sqlite3_close(db);
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_prepare_v2 to sqlite3_column_bytes16

    int ret_sqlite3_column_bytes16_lweqn = sqlite3_column_bytes16(NULL, rc);
    if (ret_sqlite3_column_bytes16_lweqn < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    snprintf(sql, sizeof(sql), "SELECT * FROM fuzz_table;");
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}