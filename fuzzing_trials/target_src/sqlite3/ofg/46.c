#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    char *errMsg = 0;
    const char *sqlCreateTable = "CREATE TABLE IF NOT EXISTS FuzzTest (id INT, data TEXT);";
    const char *sqlInsert = "INSERT INTO FuzzTest (id, data) VALUES (1, 'SampleData');";
    const char *sqlSelect = "SELECT * FROM FuzzTest;";

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Create table
    rc = sqlite3_exec(db, sqlCreateTable, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Insert data
    rc = sqlite3_exec(db, sqlInsert, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare select statement
    rc = sqlite3_prepare_v2(db, sqlSelect, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement and call sqlite3_column_type
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int columnCount = sqlite3_column_count(stmt);
        for (int i = 0; i < columnCount; i++) {
            int columnType = sqlite3_column_type(stmt, i);
            // Use columnType for further processing if needed
        }
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}