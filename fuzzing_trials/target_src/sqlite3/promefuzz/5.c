// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_parameter_count at sqlite3.c:80264:16 in sqlite3.h
// sqlite3_bind_parameter_name at sqlite3.c:80275:24 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_malloc64 at sqlite3.c:17383:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_bind_text64 at sqlite3.c:80167:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

static sqlite3_stmt* prepare_dummy_statement(sqlite3* db) {
    sqlite3_stmt* stmt = NULL;
    if (db) {
        const char* sql = "SELECT ?1, :param2, $param3, @param4";
        sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    }
    return stmt;
}

int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    sqlite3* db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    sqlite3_stmt* stmt = prepare_dummy_statement(db);
    if (!stmt) {
        sqlite3_close(db);
        return 0;
    }

    int param_count = sqlite3_bind_parameter_count(stmt);
    for (int i = 1; i <= param_count; ++i) {
        const char* param_name = sqlite3_bind_parameter_name(stmt, i);
        if (param_name) {
            sqlite3_bind_int(stmt, i, i);
        }
    }

    if (Size > 0) {
        sqlite3_uint64 alloc_size = (sqlite3_uint64)Data[0];
        void* mem = sqlite3_malloc64(alloc_size);
        if (mem) {
            memset(mem, 0, alloc_size);
            sqlite3_free(mem);
        }

        if (Size > 1) {
            const char* text = (const char*)Data + 1;
            sqlite3_uint64 text_len = Size - 1;
            sqlite3_bind_text64(stmt, 1, text, text_len, SQLITE_TRANSIENT, SQLITE_UTF8);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}