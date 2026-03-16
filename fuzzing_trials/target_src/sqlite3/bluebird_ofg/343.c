#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_343(const uint8_t *data, size_t size) {
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

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_close with sqlite3_error_offset
        sqlite3_error_offset(db);
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_exec to sqlite3_prepare_v2
    int ret_sqlite3_get_autocommit_cpymq = sqlite3_get_autocommit(db);
    if (ret_sqlite3_get_autocommit_cpymq < 0){
    	return 0;
    }
    int ret_sqlite3_test_control_jfdxv = sqlite3_test_control(0);
    if (ret_sqlite3_test_control_jfdxv < 0){
    	return 0;
    }
    sqlite3_stmt *hkhuiknh;
    memset(&hkhuiknh, 0, sizeof(hkhuiknh));
    const char *gvphxcds[1024] = {"teddw", NULL};

    int ret_sqlite3_prepare_v2_tpixt = sqlite3_prepare_v2(db, errMsg, ret_sqlite3_test_control_jfdxv, &hkhuiknh, gvphxcds);
    if (ret_sqlite3_prepare_v2_tpixt < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(sql);
    sqlite3_close(db);

    return 0;
}