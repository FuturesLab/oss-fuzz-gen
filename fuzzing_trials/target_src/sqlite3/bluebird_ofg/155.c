#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
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
    sqlite3_exec(db, sql, 0, 0, &errMsg);

    // Free allocated resources
    if (errMsg) {
        sqlite3_free(errMsg);
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_exec to sqlite3_db_readonly

    int ret_sqlite3_db_readonly_pugqm = sqlite3_db_readonly(db, NULL);
    if (ret_sqlite3_db_readonly_pugqm < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_db_readonly to sqlite3_wal_autocheckpoint
    int ret_sqlite3_compileoption_used_fmkfn = sqlite3_compileoption_used((const char *)"w");
    if (ret_sqlite3_compileoption_used_fmkfn < 0){
    	return 0;
    }

    int ret_sqlite3_wal_autocheckpoint_uipxx = sqlite3_wal_autocheckpoint(db, ret_sqlite3_compileoption_used_fmkfn);
    if (ret_sqlite3_wal_autocheckpoint_uipxx < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(sql);
    sqlite3_close(db);

    return 0;
}