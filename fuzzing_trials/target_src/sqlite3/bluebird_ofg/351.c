#include "sqlite3.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_351(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    
    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Ensure the data is null-terminated to prevent buffer overflow issues
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute some SQL commands to potentially generate an error
    char *errMsg = NULL;
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
    }

    // Call the function-under-test
    const void *errmsg = sqlite3_errmsg16(db);

    // Cleanup
    free(sql);
    sqlite3_close(db);

    return 0;
}