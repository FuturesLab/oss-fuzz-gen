// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_sleep at sqlite3.c:175133:16 in sqlite3.h
// sqlite3_threadsafe at sqlite3.c:171135:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_changes at sqlite3.c:172160:16 in sqlite3.h
// sqlite3_db_status at sqlite3.c:11036:16 in sqlite3.h
// sqlite3_busy_timeout at sqlite3.c:172853:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sqlite3.h>

static void fuzz_sqlite3_sleep(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int ms = *((int*)Data);
    sqlite3_sleep(ms);
}

static void fuzz_sqlite3_threadsafe(void) {
    sqlite3_threadsafe();
}

static void fuzz_sqlite3_open(const uint8_t *Data, size_t Size) {
    char *filename = NULL;
    sqlite3 *db = NULL;
    
    if (Size > 0) {
        filename = malloc(Size + 1);
        if (filename == NULL) return;
        memcpy(filename, Data, Size);
        filename[Size] = '\0';
    }
    
    sqlite3_open(filename ? filename : "./dummy_file", &db);
    
    if (db) {
        sqlite3_close(db);
    }
    
    free(filename);
}

static void fuzz_sqlite3_changes(sqlite3 *db) {
    sqlite3_changes(db);
}

static void fuzz_sqlite3_db_status(sqlite3 *db) {
    int cur = 0, hiwtr = 0;
    sqlite3_db_status(db, SQLITE_DBSTATUS_LOOKASIDE_USED, &cur, &hiwtr, 0);
}

static void fuzz_sqlite3_busy_timeout(sqlite3 *db, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int ms = *((int*)Data);
    sqlite3_busy_timeout(db, ms);
}

int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    int rc = sqlite3_open("./dummy_file", &db);
    if (rc != SQLITE_OK) return 0;

    fuzz_sqlite3_sleep(Data, Size);
    fuzz_sqlite3_threadsafe();
    fuzz_sqlite3_open(Data, Size);
    fuzz_sqlite3_changes(db);
    fuzz_sqlite3_db_status(db);
    fuzz_sqlite3_busy_timeout(db, Data, Size);

    sqlite3_close(db);
    return 0;
}