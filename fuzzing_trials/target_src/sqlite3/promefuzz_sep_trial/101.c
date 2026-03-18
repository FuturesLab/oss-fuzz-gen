// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_get_table at sqlite3.c:141812:16 in sqlite3.h
// sqlite3_free_table at sqlite3.c:141881:17 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_column_count at sqlite3.c:79599:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_table_column_metadata at sqlite3.c:175018:16 in sqlite3.h
// sqlite3_set_authorizer at sqlite3.c:110840:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int dummy_callback(void *unused, int argc, char **argv, char **colName) {
    (void)unused;
    (void)argc;
    (void)argv;
    (void)colName;
    return 0;
}

static int dummy_authorizer(void *pUserData, int action, const char *param1, const char *param2, const char *param3, const char *param4) {
    (void)pUserData;
    (void)action;
    (void)param1;
    (void)param2;
    (void)param3;
    (void)param4;
    return SQLITE_OK;
}

int LLVMFuzzerTestOneInput_101(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    char *errMsg = NULL;
    char **result;
    int rc, nRow, nCol;
    const char *tail;
    char *sql = NULL;
    char *zErrMsg = NULL;
    const char *dataType, *collSeq;
    int notNull, primaryKey, autoinc;

    // Create a dummy database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare SQL statement from fuzz data
    sql = malloc(Size + 1);
    if (!sql) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, Data, Size);
    sql[Size] = '\0';

    // Execute the SQL statement using sqlite3_exec
    rc = sqlite3_exec(db, sql, dummy_callback, NULL, &errMsg);
    if (rc != SQLITE_OK && errMsg) {
        sqlite3_free(errMsg);
    }

    // Test sqlite3_get_table
    rc = sqlite3_get_table(db, sql, &result, &nRow, &nCol, &zErrMsg);
    if (rc == SQLITE_OK) {
        sqlite3_free_table(result);
    } else if (zErrMsg) {
        sqlite3_free(zErrMsg);
    }

    // Test sqlite3_prepare_v2
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &tail);
    if (rc == SQLITE_OK) {
        // Test sqlite3_column_count
        int colCount = sqlite3_column_count(stmt);
        (void)colCount;
        sqlite3_finalize(stmt);
    }

    // Test sqlite3_table_column_metadata
    rc = sqlite3_table_column_metadata(db, "main", "dummy_table", "dummy_column", &dataType, &collSeq, &notNull, &primaryKey, &autoinc);
    (void)dataType;
    (void)collSeq;
    (void)notNull;
    (void)primaryKey;
    (void)autoinc;

    // Test sqlite3_set_authorizer
    rc = sqlite3_set_authorizer(db, dummy_authorizer, NULL);

    // Clean up
    free(sql);
    sqlite3_close(db);

    return 0;
}