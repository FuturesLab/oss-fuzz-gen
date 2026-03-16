#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_186(const uint8_t *data, size_t size) {
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
    char *ggwrttvt[1024] = {"nabhk", NULL};
    sqlite3_exec(db, sql, 0, 0, ggwrttvt);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Free allocated resources
    if (errMsg) {
        sqlite3_free(errMsg);
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_exec to sqlite3_str_appendall
    sqlite3_str* ret_sqlite3_str_new_ztedw = sqlite3_str_new(NULL);
    if (ret_sqlite3_str_new_ztedw == NULL){
    	return 0;
    }

    sqlite3_str_appendall(ret_sqlite3_str_new_ztedw, *ggwrttvt);

    // End mutation: Producer.APPEND_MUTATOR

    free(sql);
    sqlite3_close(db);

    return 0;
}