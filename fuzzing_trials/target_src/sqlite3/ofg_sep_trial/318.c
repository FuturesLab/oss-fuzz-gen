#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_318(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    char *errMsg = 0;
    const char *sql;
    const char *errmsg;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    // Convert fuzzer input to a null-terminated string
    sql = (const char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy((char *)sql, data, size);
    ((char *)sql)[size] = '\0';

    // Execute SQL statement
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        // Call the function-under-test
        errmsg = sqlite3_errmsg(db);
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errMsg);
    }

    // Clean up
    free((char *)sql);
    sqlite3_close(db);

    return 0;
}