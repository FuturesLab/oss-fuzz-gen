#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_389(const uint8_t *data, size_t size) {
    // Initialize SQLite database
    sqlite3 *db;
    char *errMsg = 0;

    // Open an in-memory SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Ensure the input data is null-terminated

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_open to sqlite3_set_last_insert_rowid
    sqlite3_int64 ret_sqlite3_changes64_ftjmi = sqlite3_changes64(db);

    sqlite3_set_last_insert_rowid(db, ret_sqlite3_changes64_ftjmi);

    // End mutation: Producer.APPEND_MUTATOR

    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute the SQL statement
    sqlite3_exec(db, sql, 0, 0, &errMsg);

    // Free allocated resources
    if (errMsg) {

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_free
        sqlite3_free(NULL);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


    }
    free(sql);
    sqlite3_close(db);

    return 0;
}