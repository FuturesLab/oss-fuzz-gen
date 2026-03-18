#include <stdint.h>
#include <stddef.h>  // Include this for size_t
#include <stdlib.h>  // Include this for NULL
#include <sqlite3.h>
#include <string.h>  // Include this for memcpy

int LLVMFuzzerTestOneInput_362(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated for SQLite to process it as a string
    char *sql = (char*)malloc(size + 1);
    if (!sql) {
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    sqlite3 *db;
    char *errMsg = NULL;

    // Open an in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        free(sql);
        return 0;
    }

    // Execute the SQL statement
    sqlite3_exec(db, sql, 0, 0, &errMsg);

    // Free error message if any
    if (errMsg) {
        sqlite3_free(errMsg);
    }

    // Close the database
    sqlite3_close(db);

    // Free the allocated SQL string
    free(sql);

    return 0;
}