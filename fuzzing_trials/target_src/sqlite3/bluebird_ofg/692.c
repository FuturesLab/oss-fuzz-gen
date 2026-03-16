#include <stdint.h>
#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_692(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    char *errMsg = 0;

    // Open a temporary in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Create a simple table
    rc = sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);", NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Ensure the input data is null-terminated and safe for sqlite3_mprintf
    char *safeData = (char *)malloc(size + 1);
    if (!safeData) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(safeData, data, size);
    safeData[size] = '\0';

    // Use the input data to insert into the table
    char *sql = sqlite3_mprintf("INSERT INTO test (value) VALUES (%Q);", safeData);
    free(safeData);
    rc = sqlite3_exec(db, sql, NULL, 0, &errMsg);
    sqlite3_free(sql);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    int changes = sqlite3_changes(db);
    printf("Number of changes: %d\n", changes);

    // Close the database
    sqlite3_close(db);

    return 0;
}