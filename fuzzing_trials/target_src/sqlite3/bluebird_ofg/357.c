#include <stdint.h>
#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_357(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *errMsg = 0;
    int rc;
    char *sql;

    // Initialize SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Create a simple table
    rc = sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);", NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare a SQL statement using the input data
    sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        free(sql);
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    int param_count = sqlite3_bind_parameter_count(stmt);
    printf("Parameter count: %d\n", param_count);

    // Cleanup
    sqlite3_finalize(stmt);
    free(sql);
    sqlite3_close(db);

    return 0;
}