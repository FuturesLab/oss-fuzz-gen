#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    // Initialize SQLite database
    sqlite3 *db;
    char *errMsg = 0;

    // Open an in-memory SQLite database

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_open
    if (sqlite3_open((const char *)"r", &db) != SQLITE_OK) {
    // End mutation: Producer.REPLACE_ARG_MUTATOR


        return 0;
    }

    // Ensure the input data is null-terminated

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_open to sqlite3_db_mutex

    sqlite3_mutex* ret_sqlite3_db_mutex_ykhfl = sqlite3_db_mutex(db);
    if (ret_sqlite3_db_mutex_ykhfl == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_close with sqlite3_is_interrupted
        sqlite3_is_interrupted(db);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


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