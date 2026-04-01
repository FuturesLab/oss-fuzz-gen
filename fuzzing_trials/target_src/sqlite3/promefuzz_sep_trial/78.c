// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_double at sqlite3.c:80104:16 in sqlite3.h
// sqlite3_bind_blob at sqlite3.c:80082:16 in sqlite3.h
// sqlite3_bind_blob64 at sqlite3.c:80094:16 in sqlite3.h
// sqlite3_transfer_bindings at sqlite3.c:80324:16 in sqlite3.h
// sqlite3_bind_zeroblob64 at sqlite3.c:80242:16 in sqlite3.h
// sqlite3_clear_bindings at sqlite3.c:78482:16 in sqlite3.h
// sqlite3_clear_bindings at sqlite3.c:78482:16 in sqlite3.h
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

static sqlite3 *db = NULL;
static sqlite3_stmt *stmt1 = NULL;
static sqlite3_stmt *stmt2 = NULL;

static void initialize_database() {
    if (db == NULL) {
        sqlite3_open(":memory:", &db);
        sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, data BLOB);", NULL, NULL, NULL);
        sqlite3_prepare_v2(db, "INSERT INTO test (data) VALUES (?);", -1, &stmt1, NULL);
        sqlite3_prepare_v2(db, "INSERT INTO test (data) VALUES (?);", -1, &stmt2, NULL);
    }
}

static void cleanup_database() {
    if (stmt1) {
        sqlite3_finalize(stmt1);
        stmt1 = NULL;
    }
    if (stmt2) {
        sqlite3_finalize(stmt2);
        stmt2 = NULL;
    }
    if (db) {
        sqlite3_close(db);
        db = NULL;
    }
}

int LLVMFuzzerTestOneInput_78(const uint8_t *Data, size_t Size) {
    initialize_database();

    if (Size < sizeof(double) + sizeof(sqlite3_uint64) + 2) {
        return 0;
    }

    double double_value;
    memcpy(&double_value, Data, sizeof(double));
    Data += sizeof(double);
    Size -= sizeof(double);

    sqlite3_uint64 blob_size;
    memcpy(&blob_size, Data, sizeof(sqlite3_uint64));
    Data += sizeof(sqlite3_uint64);
    Size -= sizeof(sqlite3_uint64);

    int index1 = Data[0] % 10 + 1;
    int index2 = Data[1] % 10 + 1;
    Data += 2;
    Size -= 2;

    sqlite3_bind_double(stmt1, index1, double_value);

    sqlite3_bind_blob(stmt1, index1, Data, Size, SQLITE_TRANSIENT);
    sqlite3_bind_blob64(stmt2, index2, Data, Size, SQLITE_TRANSIENT);

    sqlite3_transfer_bindings(stmt1, stmt2);
    sqlite3_bind_zeroblob64(stmt1, index1, blob_size);

    sqlite3_clear_bindings(stmt1);
    sqlite3_clear_bindings(stmt2);

    cleanup_database();
    return 0;
}