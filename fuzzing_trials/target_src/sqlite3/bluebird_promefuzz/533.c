#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include <stdlib.h>
#include "stdio.h"
#include "sqlite3.h"

static sqlite3_stmt* prepare_dummy_statement(sqlite3* db) {
    sqlite3_stmt* stmt = NULL;
    if (db) {
        const char* sql = "SELECT ?1, :param2, $param3, @param4";
        sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    }
    return stmt;
}

int LLVMFuzzerTestOneInput_533(const uint8_t *Data, size_t Size) {
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