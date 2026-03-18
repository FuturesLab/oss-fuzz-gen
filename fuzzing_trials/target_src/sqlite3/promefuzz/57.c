// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_db_status at sqlite3.c:11036:16 in sqlite3.h
// sqlite3_error_offset at sqlite3.c:173770:16 in sqlite3.h
// sqlite3_changes at sqlite3.c:172160:16 in sqlite3.h
// sqlite3_extended_result_codes at sqlite3.c:175149:16 in sqlite3.h
// sqlite3_total_changes at sqlite3.c:172176:16 in sqlite3.h
// sqlite3_errcode at sqlite3.c:173827:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <sqlite3.h>

static sqlite3 *open_database() {
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return NULL;
    }
    return db;
}

static void close_database(sqlite3 *db) {
    if (db) {
        sqlite3_close(db);
    }
}

int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 2) {
        return 0;
    }

    sqlite3 *db = open_database();
    if (!db) {
        return 0;
    }

    int op = *((int *)Data);
    int resetFlg = *((int *)(Data + sizeof(int)));
    int cur, hiwtr;

    // Fuzz sqlite3_db_status
    sqlite3_db_status(db, op, &cur, &hiwtr, resetFlg);

    // Fuzz sqlite3_error_offset
    sqlite3_error_offset(db);

    // Fuzz sqlite3_changes
    sqlite3_changes(db);

    // Fuzz sqlite3_extended_result_codes
    int onoff = Data[Size - 1] % 2; // Use last byte to decide on/off
    sqlite3_extended_result_codes(db, onoff);

    // Fuzz sqlite3_total_changes
    sqlite3_total_changes(db);

    // Fuzz sqlite3_errcode
    sqlite3_errcode(db);

    close_database(db);
    return 0;
}