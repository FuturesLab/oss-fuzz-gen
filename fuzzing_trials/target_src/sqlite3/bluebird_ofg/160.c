#include <stdint.h>
#include "sqlite3.h"
#include <stdio.h>
#include <string.h>

// Fuzzing harness for sqlite3_total_changes
int LLVMFuzzerTestOneInput_160(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    
    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Ensure the data is null-terminated before using it as a string
    char *sql = (char *)malloc(size + 1);
    if (!sql) {
        fprintf(stderr, "Memory allocation failed\n");
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute some SQL commands if data is available
    if (size > 0) {
        char *errMsg = 0;
        rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            sqlite3_free(errMsg);
        }
    }

    // Call the function under test
    int changes = sqlite3_total_changes(db);
    printf("Total changes: %d\n", changes);

    // Clean up
    free(sql);
    sqlite3_close(db);

    return 0;
}