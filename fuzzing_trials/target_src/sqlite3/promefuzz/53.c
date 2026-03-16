// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_prepare16_v2 at sqlite3.c:132700:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_prepare at sqlite3.c:132560:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_prepare_v3 at sqlite3.c:132590:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_prepare16_v3 at sqlite3.c:132712:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_prepare16 at sqlite3.c:132688:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_column_decltype16 at sqlite3.c:79910:24 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

static void execute_sqlite3_prepare16_v2(sqlite3 *db, const uint8_t *Data, size_t Size) {
    sqlite3_stmt *stmt = NULL;
    const void *pzTail = NULL;
    if (Size % 2 == 0) { // Ensure Size is even for UTF-16
        int rc = sqlite3_prepare16_v2(db, Data, (int)Size, &stmt, &pzTail);
        if (rc == SQLITE_OK && stmt) {
            sqlite3_finalize(stmt);
        }
    }
}

static void execute_sqlite3_prepare(sqlite3 *db, const uint8_t *Data, size_t Size) {
    sqlite3_stmt *stmt = NULL;
    const char *pzTail = NULL;
    int rc = sqlite3_prepare(db, (const char *)Data, (int)Size, &stmt, &pzTail);
    if (rc == SQLITE_OK && stmt) {
        sqlite3_finalize(stmt);
    }
}

static void execute_sqlite3_prepare_v3(sqlite3 *db, const uint8_t *Data, size_t Size) {
    sqlite3_stmt *stmt = NULL;
    const char *pzTail = NULL;
    unsigned int prepFlags = 0;
    int rc = sqlite3_prepare_v3(db, (const char *)Data, (int)Size, prepFlags, &stmt, &pzTail);
    if (rc == SQLITE_OK && stmt) {
        sqlite3_finalize(stmt);
    }
}

static void execute_sqlite3_prepare16_v3(sqlite3 *db, const uint8_t *Data, size_t Size) {
    sqlite3_stmt *stmt = NULL;
    const void *pzTail = NULL;
    unsigned int prepFlags = 0;
    if (Size % 2 == 0) { // Ensure Size is even for UTF-16
        int rc = sqlite3_prepare16_v3(db, Data, (int)Size, prepFlags, &stmt, &pzTail);
        if (rc == SQLITE_OK && stmt) {
            sqlite3_finalize(stmt);
        }
    }
}

static void execute_sqlite3_prepare16(sqlite3 *db, const uint8_t *Data, size_t Size) {
    sqlite3_stmt *stmt = NULL;
    const void *pzTail = NULL;
    if (Size % 2 == 0) { // Ensure Size is even for UTF-16
        int rc = sqlite3_prepare16(db, Data, (int)Size, &stmt, &pzTail);
        if (rc == SQLITE_OK && stmt) {
            sqlite3_finalize(stmt);
        }
    }
}

static void execute_sqlite3_column_decltype16(sqlite3_stmt *stmt, int column) {
    const void *declType = sqlite3_column_decltype16(stmt, column);
    (void)declType; // Use declType if needed
}

int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db = NULL;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    execute_sqlite3_prepare16_v2(db, Data, Size);
    execute_sqlite3_prepare(db, Data, Size);
    execute_sqlite3_prepare_v3(db, Data, Size);
    execute_sqlite3_prepare16_v3(db, Data, Size);
    execute_sqlite3_prepare16(db, Data, Size);

    sqlite3_stmt *stmt = NULL;
    rc = sqlite3_prepare_v2(db, (const char *)Data, (int)Size, &stmt, NULL);
    if (rc == SQLITE_OK && stmt) {
        execute_sqlite3_column_decltype16(stmt, 0);
        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
    return 0;
}