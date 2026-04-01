// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_keyword_name at sqlite3.c:169864:16 in sqlite3.h
// sqlite3_column_blob at sqlite3.c:79714:24 in sqlite3.h
// sqlite3_keyword_count at sqlite3.c:169871:16 in sqlite3.h
// sqlite3_column_type at sqlite3.c:79770:16 in sqlite3.h
// sqlite3_keyword_check at sqlite3.c:169872:16 in sqlite3.h
// sqlite3_error_offset at sqlite3.c:173770:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

static void fuzz_sqlite3_keyword_name(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int index = *(int*)Data;
    const char *keyword;
    int length;
    sqlite3_keyword_name(index, &keyword, &length);
}

static void fuzz_sqlite3_column_blob(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(sqlite3_stmt*) + sizeof(int)) return;
    sqlite3_stmt *stmt = NULL; // Initialize to NULL to prevent invalid dereference
    int iCol = *(int*)(Data + sizeof(sqlite3_stmt*));
    sqlite3_column_blob(stmt, iCol);
}

static void fuzz_sqlite3_keyword_count() {
    sqlite3_keyword_count();
}

static void fuzz_sqlite3_column_type(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(sqlite3_stmt*) + sizeof(int)) return;
    sqlite3_stmt *stmt = NULL; // Initialize to NULL to prevent invalid dereference
    int iCol = *(int*)(Data + sizeof(sqlite3_stmt*));
    sqlite3_column_type(stmt, iCol);
}

static void fuzz_sqlite3_keyword_check(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    sqlite3_keyword_check((const char*)Data, (int)Size);
}

static void fuzz_sqlite3_error_offset(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(sqlite3*)) return;
    sqlite3 *db = NULL; // Initialize to NULL to prevent invalid dereference
    sqlite3_error_offset(db);
}

int LLVMFuzzerTestOneInput_80(const uint8_t *Data, size_t Size) {
    fuzz_sqlite3_keyword_name(Data, Size);
    fuzz_sqlite3_column_blob(Data, Size);
    fuzz_sqlite3_keyword_count();
    fuzz_sqlite3_column_type(Data, Size);
    fuzz_sqlite3_keyword_check(Data, Size);
    fuzz_sqlite3_error_offset(Data, Size);
    return 0;
}