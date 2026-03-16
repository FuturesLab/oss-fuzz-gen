#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include <stdlib.h>
#include "stdio.h"
#include "sqlite3.h"
#include "stdint.h"
#include "stddef.h"
#include "string.h"

static void prepareDatabase(sqlite3 **db) {
    int rc = sqlite3_open(":memory:", db);
    if (rc != SQLITE_OK) {
        *db = NULL;
    }
}

static void prepareStatement(sqlite3 *db, const char *sql, sqlite3_stmt **stmt) {
    if (db == NULL) {
        *stmt = NULL;
        return;
    }
    int rc = sqlite3_prepare_v2(db, sql, -1, stmt, NULL);
    if (rc != SQLITE_OK) {
        *stmt = NULL;
    }
}

int LLVMFuzzerTestOneInput_505(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    sqlite3_stmt *nextStmt = NULL;
    sqlite3 *dbHandle = NULL;
    int rc;

    // Prepare database
    prepareDatabase(&db);

    // Prepare a statement if possible
    if (Size > 0) {
        char *sql = (char *)malloc(Size + 1);
        if (sql != NULL) {
            memcpy(sql, Data, Size);
            sql[Size] = '\0'; // Null-terminate the SQL string
            prepareStatement(db, sql, &stmt);
            free(sql);
        }
    }

    // Test sqlite3_db_handle
    dbHandle = sqlite3_db_handle(stmt);

    // Test sqlite3_next_stmt
    nextStmt = sqlite3_next_stmt(db, NULL);
    nextStmt = sqlite3_next_stmt(db, stmt);

    // Ensure Data is large enough for UTF-16 operations
    if (Size % 2 == 0) {
        // Test sqlite3_prepare16_v3
        rc = sqlite3_prepare16_v3(db, Data, (int)Size, 0, &stmt, NULL);

        // Test sqlite3_prepare16_v2
        rc = sqlite3_prepare16_v2(db, Data, (int)Size, &stmt, NULL);
    }

    // Test sqlite3_prepare
    rc = sqlite3_prepare(db, (const char *)Data, (int)Size, &stmt, NULL);

    // Test sqlite3_prepare_v3
    rc = sqlite3_prepare_v3(db, (const char *)Data, (int)Size, 0, &stmt, NULL);

    // Cleanup
    if (stmt) {
        sqlite3_finalize(stmt);
    }
    if (db) {
        sqlite3_close(db);
    }

    return 0;
}