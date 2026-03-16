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

int LLVMFuzzerTestOneInput_133(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_open
    rc = sqlite3_open((const char *)"r", &db);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (rc != SQLITE_OK) {
        free(sql);
        return 0;
    }

    // Execute SQL

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 4 of sqlite3_exec
    rc = sqlite3_exec(db, sql, callback, 0, NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_malloc
    void *ptr = sqlite3_malloc(-1);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ptr) {
        memcpy(ptr, Data, Size);
        sqlite3_free(ptr);
    }

    // Close the database connection
    sqlite3_close(db);
    free(sql);
    return 0;
}