// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open16 at sqlite3.c:174715:16 in sqlite3.h
// sqlite3_prepare16_v2 at sqlite3.c:132700:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_prepare16_v3 at sqlite3.c:132712:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_bind_text16 at sqlite3.c:80183:16 in sqlite3.h
// sqlite3_create_collation16 at sqlite3.c:174792:16 in sqlite3.h
// sqlite3_create_collation16 at sqlite3.c:174792:16 in sqlite3.h
// sqlite3_prepare16 at sqlite3.c:132688:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

static int custom_collation(void* pArg, int len1, const void* str1, int len2, const void* str2) {
    // Simple collation function for demonstration purposes
    return memcmp(str1, str2, len1 < len2 ? len1 : len2);
}

int LLVMFuzzerTestOneInput_105(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    const void *tail = NULL;
    int rc;

    // Ensure data is long enough to be used for various operations
    if (Size < 4 || Size % 2 != 0) return 0; // Ensure even length for UTF-16

    // Prepare a dummy UTF-16 SQL statement
    const void *sql = (const void *)Data;
    int sqlSize = (int)Size;

    // Open a database connection
    rc = sqlite3_open16(u"./dummy_file", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Test sqlite3_prepare16_v2
    rc = sqlite3_prepare16_v2(db, sql, sqlSize, &stmt, &tail);
    if (rc == SQLITE_OK && stmt) {
        sqlite3_finalize(stmt);
    }

    // Test sqlite3_prepare16_v3
    rc = sqlite3_prepare16_v3(db, sql, sqlSize, 0, &stmt, &tail);
    if (rc == SQLITE_OK && stmt) {
        sqlite3_finalize(stmt);
    }

    // Test sqlite3_bind_text16
    if (stmt) {
        sqlite3_bind_text16(stmt, 1, sql, sqlSize, SQLITE_STATIC);
    }

    // Ensure null-terminated UTF-16 string for collation
    if (sqlSize >= 2 && ((const uint16_t*)sql)[sqlSize/2 - 1] != 0) {
        uint16_t *nullTerminatedSql = malloc(sqlSize + 2);
        if (nullTerminatedSql) {
            memcpy(nullTerminatedSql, sql, sqlSize);
            nullTerminatedSql[sqlSize/2] = 0;
            rc = sqlite3_create_collation16(db, nullTerminatedSql, SQLITE_UTF16, NULL, custom_collation);
            free(nullTerminatedSql);
        }
    } else {
        rc = sqlite3_create_collation16(db, sql, SQLITE_UTF16, NULL, custom_collation);
    }

    // Test sqlite3_prepare16
    rc = sqlite3_prepare16(db, sql, sqlSize, &stmt, &tail);
    if (rc == SQLITE_OK && stmt) {
        sqlite3_finalize(stmt);
    }

    // Clean up
    sqlite3_close(db);

    return 0;
}