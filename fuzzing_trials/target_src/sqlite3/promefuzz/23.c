// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_int64 at sqlite3.c:80118:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_int64 at sqlite3.c:80118:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_int64 at sqlite3.c:80118:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_libversion_number at sqlite3.c:171129:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
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
#include <string.h>

static sqlite3_stmt* prepare_dummy_stmt(sqlite3* db) {
    const char* sql = "SELECT * FROM dummy WHERE id = ?";
    sqlite3_stmt* stmt = NULL;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }
    return stmt;
}

int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    sqlite3* db = NULL;
    sqlite3_stmt* stmt = NULL;
    int rc = SQLITE_OK;

    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    stmt = prepare_dummy_stmt(db);
    if (!stmt) {
        sqlite3_close(db);
        return 0;
    }

    if (Size < 8) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    int idx = 0;
    sqlite3_int64 int64_val = *((sqlite3_int64*)(&Data[idx]));
    idx += sizeof(sqlite3_int64);

    rc = sqlite3_bind_int64(stmt, 1, int64_val);
    rc = sqlite3_bind_int(stmt, 2, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_text(stmt, 3, (const char*)&Data[idx], (int)(Size - idx), SQLITE_STATIC);
    rc = sqlite3_bind_int(stmt, 4, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_int64(stmt, 5, int64_val);
    rc = sqlite3_bind_text(stmt, 6, (const char*)&Data[idx], (int)(Size - idx), SQLITE_STATIC);
    rc = sqlite3_bind_int(stmt, 7, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_int64(stmt, 8, int64_val);
    rc = sqlite3_bind_text(stmt, 9, (const char*)&Data[idx], (int)(Size - idx), SQLITE_STATIC);
    rc = sqlite3_bind_int(stmt, 10, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_int(stmt, 11, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_text(stmt, 12, (const char*)&Data[idx], (int)(Size - idx), SQLITE_STATIC);
    rc = sqlite3_bind_text(stmt, 13, (const char*)&Data[idx], (int)(Size - idx), SQLITE_STATIC);
    rc = sqlite3_bind_text(stmt, 14, (const char*)&Data[idx], (int)(Size - idx), SQLITE_STATIC);
    rc = sqlite3_bind_int(stmt, 15, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_int(stmt, 16, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_int(stmt, 17, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_int(stmt, 18, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_text(stmt, 19, (const char*)&Data[idx], (int)(Size - idx), SQLITE_STATIC);
    rc = sqlite3_bind_int(stmt, 20, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_int(stmt, 21, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_int(stmt, 22, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_int(stmt, 23, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_int(stmt, 24, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_int(stmt, 25, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_int(stmt, 26, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_int(stmt, 27, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_int(stmt, 28, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_int(stmt, 29, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_text(stmt, 30, (const char*)&Data[idx], (int)(Size - idx), SQLITE_STATIC);
    rc = sqlite3_bind_int(stmt, 31, (int)Data[idx++ % Size]);

    int version = sqlite3_libversion_number();

    rc = sqlite3_bind_int(stmt, 32, (int)Data[idx++ % Size]);
    rc = sqlite3_bind_text(stmt, 33, (const char*)&Data[idx], (int)(Size - idx), SQLITE_STATIC);
    rc = sqlite3_bind_text(stmt, 34, (const char*)&Data[idx], (int)(Size - idx), SQLITE_STATIC);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}