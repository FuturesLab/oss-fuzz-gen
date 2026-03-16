// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_prepare at sqlite3.c:132560:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_prepare_v3 at sqlite3.c:132590:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_prepare16_v2 at sqlite3.c:132700:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_prepare16_v3 at sqlite3.c:132712:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_next_stmt at sqlite3.c:80418:26 in sqlite3.h
// sqlite3_next_stmt at sqlite3.c:80418:26 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_db_handle at sqlite3.c:80348:21 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void prepareDatabase(sqlite3 **db) {
    if (sqlite3_open("./dummy_file", db) != SQLITE_OK) {
        *db = NULL;
    }
}

static void cleanupDatabase(sqlite3 *db) {
    if (db) {
        sqlite3_close(db);
    }
}

static void fuzz_sqlite3_prepare(sqlite3 *db, const char *sql, int sqlSize) {
    sqlite3_stmt *stmt = NULL;
    const char *pzTail = NULL;
    sqlite3_prepare(db, sql, sqlSize, &stmt, &pzTail);
    if (stmt) {
        sqlite3_finalize(stmt);
    }
}

static void fuzz_sqlite3_prepare_v3(sqlite3 *db, const char *sql, int sqlSize) {
    sqlite3_stmt *stmt = NULL;
    const char *pzTail = NULL;
    sqlite3_prepare_v3(db, sql, sqlSize, 0, &stmt, &pzTail);
    if (stmt) {
        sqlite3_finalize(stmt);
    }
}

static void fuzz_sqlite3_prepare16_v2(sqlite3 *db, const void *sql, int sqlSize) {
    sqlite3_stmt *stmt = NULL;
    const void *pzTail = NULL;
    sqlite3_prepare16_v2(db, sql, sqlSize, &stmt, &pzTail);
    if (stmt) {
        sqlite3_finalize(stmt);
    }
}

static void fuzz_sqlite3_prepare16_v3(sqlite3 *db, const void *sql, int sqlSize) {
    sqlite3_stmt *stmt = NULL;
    const void *pzTail = NULL;
    sqlite3_prepare16_v3(db, sql, sqlSize, 0, &stmt, &pzTail);
    if (stmt) {
        sqlite3_finalize(stmt);
    }
}

static void fuzz_sqlite3_next_stmt(sqlite3 *db) {
    sqlite3_stmt *stmt = sqlite3_next_stmt(db, NULL);
    while (stmt) {
        stmt = sqlite3_next_stmt(db, stmt);
    }
}

static void fuzz_sqlite3_db_handle(sqlite3 *db, const char *sql, int sqlSize) {
    sqlite3_stmt *stmt = NULL;
    sqlite3_prepare_v2(db, sql, sqlSize, &stmt, NULL);
    if (stmt) {
        sqlite3 *dbHandle = sqlite3_db_handle(stmt);
        (void)dbHandle;
        sqlite3_finalize(stmt);
    }
}

int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    sqlite3 *db = NULL;
    prepareDatabase(&db);
    if (!db) return 0;

    char *sql = (char *)malloc(Size + 1);
    if (!sql) {
        cleanupDatabase(db);
        return 0;
    }

    memcpy(sql, Data, Size);
    sql[Size] = '\0';

    fuzz_sqlite3_prepare(db, sql, Size);
    fuzz_sqlite3_prepare_v3(db, sql, Size);
    fuzz_sqlite3_prepare16_v2(db, sql, Size);
    fuzz_sqlite3_prepare16_v3(db, sql, Size);
    fuzz_sqlite3_next_stmt(db);
    fuzz_sqlite3_db_handle(db, sql, Size);

    free(sql);
    cleanupDatabase(db);
    return 0;
}