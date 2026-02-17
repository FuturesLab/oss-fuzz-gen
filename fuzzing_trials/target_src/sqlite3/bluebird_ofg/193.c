#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_193(const uint8_t *data, size_t size) {
    // Ensure that the input data is not NULL and has a valid size
    if (data == NULL || size == 0) {
        return 0;
    }

    // Create a new SQLite database in memory
    sqlite3 *db;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_open
    if (sqlite3_open((const char *)"r", &db) != SQLITE_OK) {
    // End mutation: Producer.REPLACE_ARG_MUTATOR


        return 0; // Failed to open database
    }

    // Prepare a SQL statement using the input data
    char *errMsg = NULL;
    char sql[256];

    // Ensure the input data is null-terminated for SQL statement
    size_t sql_length = size < sizeof(sql) - 1 ? size : sizeof(sql) - 1;
    memcpy(sql, data, sql_length);
    sql[sql_length] = '\0'; // Null-terminate the SQL statement

    // Execute the SQL statement

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 4 of sqlite3_exec
    if (sqlite3_exec(db, sql, 0, 0, NULL) != SQLITE_OK) {
    // End mutation: Producer.REPLACE_ARG_MUTATOR


        // Handle the error (could log it or just ignore for fuzzing)
        sqlite3_free(errMsg);
    }

    // Close the database connection

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_close to sqlite3_wal_autocheckpoint

    int ret_sqlite3_wal_autocheckpoint_hfihb = sqlite3_wal_autocheckpoint(db, size);
    if (ret_sqlite3_wal_autocheckpoint_hfihb < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_close with sqlite3_total_changes
    sqlite3_total_changes(db);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    return 0;
}