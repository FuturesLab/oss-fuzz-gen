#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

// Define a callback function to be used with sqlite3_trace
static void traceCallback(void *unused, const char *sql) {
    (void)unused; // Avoid unused parameter warning
    // Just print the SQL statement being traced
    printf("SQL Trace: %s\n", sql);
}

int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    char *errMsg = 0;

    // Initialize SQLite database in-memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // If opening the database fails, exit early
    }

    // Ensure data is null-terminated before using it as a SQL statement
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Set the trace callback
    sqlite3_trace(db, traceCallback, NULL);

    // Execute the SQL statement
    sqlite3_exec(db, sql, 0, 0, &errMsg);

    // Clean up
    if (errMsg) {
        sqlite3_free(errMsg);
    }
    free(sql);
    sqlite3_close(db);

    return 0;
}