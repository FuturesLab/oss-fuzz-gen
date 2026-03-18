// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_db_mutex at sqlite3.c:171901:27 in sqlite3.h
// sqlite3_mutex_enter at sqlite3.c:15902:17 in sqlite3.h
// sqlite3_mutex_held at sqlite3.c:15943:16 in sqlite3.h
// sqlite3_mutex_leave at sqlite3.c:15928:17 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_92(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    sqlite3_mutex *mutex = sqlite3_db_mutex(db);
    if (mutex) {
        sqlite3_mutex_enter(mutex);
        if (sqlite3_mutex_held(mutex)) {
            sqlite3_mutex_leave(mutex);
        }
    }

    sqlite3_close(db);
    return 0;
}