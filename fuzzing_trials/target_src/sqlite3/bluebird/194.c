#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_194(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errMsg = 0;
    char *sql;
    int rc;

    // Initialize SQLite database in memory

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_open
    rc = sqlite3_open((const char *)data, &db);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (rc) {
        return 0; // Failed to open database
    }

    // Allocate memory for the SQL statement
    sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0; // Memory allocation failed
    }

    // Copy input data to sql and null-terminate it
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute the SQL statement
    rc = sqlite3_exec(db, sql, NULL, NULL, &errMsg);

    // Clean up
    free(sql);
    sqlite3_free(errMsg);
    sqlite3_close(db);

    return 0;
}