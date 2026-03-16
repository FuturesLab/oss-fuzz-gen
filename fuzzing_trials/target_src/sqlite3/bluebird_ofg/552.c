#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_552(const uint8_t *data, size_t size) {
    // Initialize SQLite database
    sqlite3 *db;
    char *errMsg = 0;

    // Open an in-memory SQLite database

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_open
    const char inmffqjj[1024] = "vyref";
    if (sqlite3_open(inmffqjj, &db) != SQLITE_OK) {
    // End mutation: Producer.REPLACE_ARG_MUTATOR


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
    sqlite3_exec(db, sql, 0, 0, NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Free allocated resources
    if (errMsg) {
        sqlite3_free(errMsg);
    }
    free(sql);
    sqlite3_close(db);

    return 0;
}