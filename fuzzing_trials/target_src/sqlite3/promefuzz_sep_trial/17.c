// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_str_new at sqlite3.c:19257:25 in sqlite3.h
// sqlite3_str_new at sqlite3.c:19257:25 in sqlite3.h
// sqlite3_str_finish at sqlite3.c:19172:18 in sqlite3.h
// sqlite3_str_finish at sqlite3.c:19172:18 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <sqlite3.h>

static void cleanup(sqlite3 *db, sqlite3_str *str1, sqlite3_str *str2, char *finishedStr1, char *finishedStr2) {
    if (db) {
        sqlite3_close(db);
    }
    if (finishedStr1) {
        sqlite3_free(finishedStr1);
    }
    if (finishedStr2) {
        sqlite3_free(finishedStr2);
    }
}

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db = NULL;
    sqlite3_str *str1 = NULL;
    sqlite3_str *str2 = NULL;
    char *finishedStr1 = NULL;
    char *finishedStr2 = NULL;

    // Open a database connection
    int rc = sqlite3_open("./dummy_file", &db);
    if (rc != SQLITE_OK) {
        cleanup(db, str1, str2, finishedStr1, finishedStr2);
        return 0;
    }

    // Create two dynamic string objects
    str1 = sqlite3_str_new(db);
    str2 = sqlite3_str_new(db);

    // Finalize the dynamic strings
    finishedStr1 = sqlite3_str_finish(str1);
    finishedStr2 = sqlite3_str_finish(str2);

    // Cleanup
    cleanup(db, str1, str2, finishedStr1, finishedStr2);

    return 0;
}