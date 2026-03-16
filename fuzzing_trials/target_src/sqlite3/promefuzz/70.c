// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_extended_result_codes at sqlite3.c:175149:16 in sqlite3.h
// sqlite3_autovacuum_pages at sqlite3.c:173449:16 in sqlite3.h
// sqlite3_create_collation_v2 at sqlite3.c:174767:16 in sqlite3.h
// sqlite3_set_clientdata at sqlite3.c:174886:16 in sqlite3.h
// sqlite3_get_clientdata at sqlite3.c:174863:18 in sqlite3.h
// sqlite3_mutex_alloc at sqlite3.c:15870:27 in sqlite3.h
// sqlite3_mutex_enter at sqlite3.c:15902:17 in sqlite3.h
// sqlite3_mutex_leave at sqlite3.c:15928:17 in sqlite3.h
// sqlite3_mutex_free at sqlite3.c:15891:17 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static int demo_autovac_pages_callback(void *pClientData, const char *zSchema, unsigned int nDbPage, unsigned int nFreePage, unsigned int nBytePerPage) {
    return nFreePage;
}

static int demo_collation_compare(void *pArg, int n1, const void *p1, int n2, const void *p2) {
    return strncmp((const char*)p1, (const char*)p2, n1 < n2 ? n1 : n2);
}

int LLVMFuzzerTestOneInput_70(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Fuzzing sqlite3_extended_result_codes
    int onoff = Data[0] % 2;
    sqlite3_extended_result_codes(db, onoff);

    // Fuzzing sqlite3_autovacuum_pages
    sqlite3_autovacuum_pages(db, demo_autovac_pages_callback, NULL, NULL);

    // Fuzzing sqlite3_create_collation_v2
    const char *collationName = "demo_collation";
    sqlite3_create_collation_v2(db, collationName, SQLITE_UTF8, NULL, demo_collation_compare, NULL);

    // Fuzzing sqlite3_get_clientdata and sqlite3_set_clientdata
    const char *clientDataName = "client_data_key";
    void *clientData = malloc(10);
    memset(clientData, 0, 10);
    sqlite3_set_clientdata(db, clientDataName, clientData, free);
    sqlite3_get_clientdata(db, clientDataName);

    // Fuzzing sqlite3_mutex_enter
    sqlite3_mutex *mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);
    if (mutex) {
        sqlite3_mutex_enter(mutex);
        sqlite3_mutex_leave(mutex);
        sqlite3_mutex_free(mutex);
    }

    sqlite3_close(db);
    return 0;
}