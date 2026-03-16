#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_637(const uint8_t *data, size_t size) {
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

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_close with sqlite3_get_autocommit
        sqlite3_get_autocommit(db);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute the SQL statement
    sqlite3_exec(db, sql, 0, 0, &errMsg);

    // Free allocated resources
    if (errMsg) {
        sqlite3_free(errMsg);
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_exec to sqlite3_db_name
    int ret_sqlite3_is_interrupted_gpori = sqlite3_is_interrupted(db);
    if (ret_sqlite3_is_interrupted_gpori < 0){
    	return 0;
    }

    const char* ret_sqlite3_db_name_evuso = sqlite3_db_name(db, ret_sqlite3_is_interrupted_gpori);
    if (ret_sqlite3_db_name_evuso == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(sql);
    sqlite3_close(db);

    return 0;
}