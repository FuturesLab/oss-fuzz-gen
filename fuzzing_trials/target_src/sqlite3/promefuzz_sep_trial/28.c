// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_int64 at sqlite3.c:80118:16 in sqlite3.h
// sqlite3_bind_double at sqlite3.c:80104:16 in sqlite3.h
// sqlite3_bind_text64 at sqlite3.c:80167:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
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
#include <string.h>

static sqlite3_stmt* prepare_dummy_stmt(sqlite3* db) {
    const char* sql = "SELECT ?1, ?2, ?3, ?4;";
    sqlite3_stmt* stmt = NULL;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }
    return stmt;
}

int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3* db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    sqlite3_stmt* stmt = prepare_dummy_stmt(db);
    if (!stmt) {
        sqlite3_close(db);
        return 0;
    }

    int param_index = 1;
    int int_value = (int)(Data[0]);
    sqlite3_int64 int64_value = (sqlite3_int64)(Data[0]);
    double double_value = (double)(Data[0]);
    const char* text_value = (const char*)Data;
    sqlite3_uint64 text_length = (sqlite3_uint64)Size;
    unsigned char encoding = SQLITE_UTF8;

    // Fuzz sqlite3_bind_int
    sqlite3_bind_int(stmt, param_index++, int_value);

    // Fuzz sqlite3_bind_int64
    sqlite3_bind_int64(stmt, param_index++, int64_value);

    // Fuzz sqlite3_bind_double
    sqlite3_bind_double(stmt, param_index++, double_value);

    // Fuzz sqlite3_bind_text64
    sqlite3_bind_text64(stmt, param_index++, text_value, text_length, SQLITE_STATIC, encoding);

    // Rebind sqlite3_bind_int to explore more states
    sqlite3_bind_int(stmt, param_index, int_value);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}