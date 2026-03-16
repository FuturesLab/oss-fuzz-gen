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

int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size) {
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

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_close with sqlite3_get_autocommit

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_get_autocommit with sqlite3_vtab_on_conflict
        sqlite3_vtab_on_conflict(db);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        // End mutation: Producer.REPLACE_FUNC_MUTATOR


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
    free(sql);
    return 0;
}