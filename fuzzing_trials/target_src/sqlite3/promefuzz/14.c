// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_limit at sqlite3.c:174006:16 in sqlite3.h
// sqlite3_limit at sqlite3.c:174006:16 in sqlite3.h
// sqlite3_limit at sqlite3.c:174006:16 in sqlite3.h
// sqlite3_limit at sqlite3.c:174006:16 in sqlite3.h
// sqlite3_hard_heap_limit64 at sqlite3.c:17198:26 in sqlite3.h
// sqlite3_test_control at sqlite3.c:175215:16 in sqlite3.h
// sqlite3_deserialize at sqlite3.c:41253:16 in sqlite3.h
// sqlite3_file_control at sqlite3.c:175162:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

static sqlite3* init_db() {
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return NULL;
    }
    return db;
}

static void cleanup_db(sqlite3 *db) {
    if (db) {
        sqlite3_close(db);
    }
}

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db = init_db();
    if (!db) return 0;

    // Fuzz sqlite3_limit
    int limitId = Data[0] % SQLITE_LIMIT_TRIGGER_DEPTH;
    int newVal = (Size > 1) ? Data[1] : -1;
    sqlite3_limit(db, limitId, newVal);
    sqlite3_limit(db, limitId, newVal);
    sqlite3_limit(db, limitId, newVal);
    sqlite3_limit(db, limitId, newVal);

    // Fuzz sqlite3_hard_heap_limit64
    sqlite3_int64 newLimit = (Size > 2) ? *((sqlite3_int64*)&Data[2]) : 1024;
    sqlite3_hard_heap_limit64(newLimit);

    // Fuzz sqlite3_test_control
    int op = (Size > 3) ? Data[3] : 0;
    sqlite3_test_control(op);

    // Prepare for sqlite3_deserialize
    unsigned char *pData = (Size > 10) ? (unsigned char*)&Data[4] : NULL;
    sqlite3_int64 szDb = (Size > 11) ? *((sqlite3_int64*)&Data[4]) : 0;
    sqlite3_int64 szBuf = (Size > 19) ? *((sqlite3_int64*)&Data[12]) : szDb;
    unsigned mFlags = (Size > 20) ? Data[20] : 0;

    // Fuzz sqlite3_deserialize
    sqlite3_deserialize(db, "main", pData, szDb, szBuf, mFlags);

    // Fuzz sqlite3_file_control
    const char *zDbName = "main";
    int fileControlOp = (Size > 21) ? Data[21] : 0;
    void *pArg = NULL;
    sqlite3_file_control(db, zDbName, fileControlOp, pArg);

    cleanup_db(db);
    return 0;
}