#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include <stdlib.h>
#include "stdio.h"
#include "sqlite3.h"

static int authorizerCallback(void *pUserData, int action, const char *arg1, const char *arg2, const char *arg3, const char *arg4) {
    return SQLITE_OK; // Allow all actions
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0; // No-op callback
}

int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    sqlite3 *db;
    char *errMsg = 0;
    char *sql = (char *)malloc(Size + 1);
    if (!sql) {
        return 0;
    }
    memcpy(sql, Data, Size);
    sql[Size] = '\0'; // Ensure null-termination

    int rc;

    // Open a database connection
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        free(sql);
        return 0;
    }

    // Execute SQL
    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
    }

    // Set authorizer
    rc = sqlite3_set_authorizer(db, authorizerCallback, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        free(sql);
        return 0;
    }

    // Table column metadata
    const char *dataType;
    const char *collSeq;
    int notNull;
    int primaryKey;
    int autoinc;
    rc = sqlite3_table_column_metadata(db, "main", "dummy_table", "dummy_column", &dataType, &collSeq, &notNull, &primaryKey, &autoinc);

    // Test control
    rc = sqlite3_test_control(SQLITE_TESTCTRL_FIRST, db);

    // Malloc
    void *ptr = sqlite3_malloc(Size);
    if (ptr) {
        memcpy(ptr, Data, Size);
        sqlite3_free(ptr);
    }

    // Close the database connection
    sqlite3_close(db);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_free to sqlite3_prepare_v3
        void* ret_sqlite3_malloc_ojhjv = sqlite3_malloc(0);
        if (ret_sqlite3_malloc_ojhjv == NULL){
        	return 0;
        }
        sqlite3_stmt *mtyurqhu;
        memset(&mtyurqhu, 0, sizeof(mtyurqhu));

        int ret_sqlite3_prepare_v3_zgfik = sqlite3_prepare_v3(NULL, (const char *)errMsg, rc, Size, &mtyurqhu, (const char **)&ret_sqlite3_malloc_ojhjv);
        if (ret_sqlite3_prepare_v3_zgfik < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_free to sqlite3_prepare16
        int ret_sqlite3_db_cacheflush_gpkyr = sqlite3_db_cacheflush(db);
        if (ret_sqlite3_db_cacheflush_gpkyr < 0){
        	return 0;
        }
        void* ret_sqlite3_malloc_obbmz = sqlite3_malloc(0);
        if (ret_sqlite3_malloc_obbmz == NULL){
        	return 0;
        }
        sqlite3_stmt *zteiopfo;
        memset(&zteiopfo, 0, sizeof(zteiopfo));

        int ret_sqlite3_prepare16_mjxvy = sqlite3_prepare16(db, ret_sqlite3_malloc_obbmz, autoinc, &zteiopfo, &ptr);
        if (ret_sqlite3_prepare16_mjxvy < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    free(sql);
    return 0;
}