#include <stdint.h>
#include "sqlite3.h"
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errmsg = 0;
    int rc;

    // Open a new in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the input data is null-terminated to prevent buffer overflow
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute the function-under-test
    if (size > 0) {
        rc = sqlite3_exec(db, sql, 0, 0, &errmsg);
        if (rc != SQLITE_OK) {
            sqlite3_free(errmsg);
        }
    }

    // Free the allocated memory
    free(sql);

    // Close the database
    sqlite3_close(db);

    return 0;
}