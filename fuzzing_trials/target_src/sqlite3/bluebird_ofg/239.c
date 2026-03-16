#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_239(const uint8_t *data, size_t size) {
    // Initialize SQLite database
    sqlite3 *db;
    char *errMsg = 0;

    // Open an in-memory SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Ensure the input data is null-terminated
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute the SQL statement

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 4 of sqlite3_exec

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of sqlite3_exec
    sqlite3_exec(db, sql, 0, (void *)"w", NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Free allocated resources
    if (errMsg) {
        sqlite3_free(errMsg);
    }
    free(sql);
    sqlite3_close(db);

    return 0;
}