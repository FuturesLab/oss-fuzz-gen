// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_keyword_name at sqlite3.c:169864:16 in sqlite3.h
// sqlite3_column_blob at sqlite3.c:79714:24 in sqlite3.h
// sqlite3_column_type at sqlite3.c:79770:16 in sqlite3.h
// sqlite3_keyword_check at sqlite3.c:169872:16 in sqlite3.h
// sqlite3_error_offset at sqlite3.c:173770:16 in sqlite3.h
// sqlite3_keyword_count at sqlite3.c:169871:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_column_count at sqlite3.c:79599:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

static void fuzz_sqlite3_keyword_name(int index) {
    const char *keyword;
    int length;
    int result = sqlite3_keyword_name(index, &keyword, &length);
    if (result == SQLITE_OK) {
        // Do something with the keyword and length, if needed
    }
}

static void fuzz_sqlite3_column_blob(sqlite3_stmt *stmt, int iCol) {
    const void *blob = sqlite3_column_blob(stmt, iCol);
    if (blob != NULL) {
        // Do something with the blob, if needed
    }
}

static void fuzz_sqlite3_column_type(sqlite3_stmt *stmt, int iCol) {
    int type = sqlite3_column_type(stmt, iCol);
    // Do something with the type, if needed
}

static void fuzz_sqlite3_keyword_check(const char *zName, int length) {
    int isKeyword = sqlite3_keyword_check(zName, length);
    // Do something with the result, if needed
}

static void fuzz_sqlite3_error_offset(sqlite3 *db) {
    int offset = sqlite3_error_offset(db);
    // Do something with the offset, if needed
}

int LLVMFuzzerTestOneInput_82(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    int index = Data[0] % sqlite3_keyword_count();
    fuzz_sqlite3_keyword_name(index);

    sqlite3 *db;
    sqlite3_open(":memory:", &db);
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT 1;", -1, &stmt, NULL);
    sqlite3_step(stmt);

    if (Size > 1) {
        int iCol = Data[1] % sqlite3_column_count(stmt);
        fuzz_sqlite3_column_blob(stmt, iCol);
        fuzz_sqlite3_column_type(stmt, iCol);
    }

    if (Size > 2) {
        const char *zName = (const char *)&Data[2];
        int length = Size - 2;
        fuzz_sqlite3_keyword_check(zName, length);
    }

    fuzz_sqlite3_error_offset(db);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}