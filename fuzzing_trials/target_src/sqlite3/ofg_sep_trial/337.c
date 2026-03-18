#include <stddef.h>  // For size_t
#include <stdlib.h>  // For NULL
#include <stdint.h>
#include <sqlite3.h>
#include <string.h>  // For memcpy

int LLVMFuzzerTestOneInput_337(const uint8_t *data, size_t size) {
    // Ensure the input data is not null and has some size
    if (data == NULL || size == 0) {
        return 0;
    }

    // Initialize SQLite database in memory
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Copy the input data to a null-terminated string
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute the SQL command
    char *errMsg = NULL;
    sqlite3_exec(db, sql, 0, 0, &errMsg);

    // Free resources
    if (errMsg) {
        sqlite3_free(errMsg);
    }
    free(sql);
    sqlite3_close(db);

    return 0;
}