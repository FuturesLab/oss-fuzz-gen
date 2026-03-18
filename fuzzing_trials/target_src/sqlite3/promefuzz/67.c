// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_mutex_alloc at sqlite3.c:15870:27 in sqlite3.h
// sqlite3_mutex_free at sqlite3.c:15891:17 in sqlite3.h
// sqlite3_mutex_notheld at sqlite3.c:15952:16 in sqlite3.h
// sqlite3_mutex_try at sqlite3.c:15913:16 in sqlite3.h
// sqlite3_mutex_held at sqlite3.c:15943:16 in sqlite3.h
// sqlite3_mutex_alloc at sqlite3.c:15870:27 in sqlite3.h
// sqlite3_mutex_leave at sqlite3.c:15928:17 in sqlite3.h
// sqlite3_mutex_free at sqlite3.c:15891:17 in sqlite3.h
// sqlite3_threadsafe at sqlite3.c:171135:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>

static int fuzz_sqlite3_mutex_alloc(int type) {
    sqlite3_mutex *mutex = sqlite3_mutex_alloc(type);
    if (mutex && (type == SQLITE_MUTEX_FAST || type == SQLITE_MUTEX_RECURSIVE)) {
        sqlite3_mutex_free(mutex);
    }
    return 0;
}

static int fuzz_sqlite3_mutex_notheld(sqlite3_mutex *mutex) {
    return sqlite3_mutex_notheld(mutex);
}

static int fuzz_sqlite3_mutex_try(sqlite3_mutex *mutex) {
    return sqlite3_mutex_try(mutex);
}

static int fuzz_sqlite3_mutex_held(sqlite3_mutex *mutex) {
    return sqlite3_mutex_held(mutex);
}

int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Limit the type to valid mutex types defined by SQLite
    int type = Data[0] % (SQLITE_MUTEX_RECURSIVE + 1); // Valid types are 0 to SQLITE_MUTEX_RECURSIVE
    sqlite3_mutex *mutex = sqlite3_mutex_alloc(type);

    if (mutex) {
        int result_notheld = fuzz_sqlite3_mutex_notheld(mutex);
        int result_try = fuzz_sqlite3_mutex_try(mutex);
        int result_held = fuzz_sqlite3_mutex_held(mutex);

        // Use the results to prevent compiler optimizations
        if (result_notheld || result_try || result_held) {
            // Do something trivial
            (void)0;
        }

        // Ensure we unlock the mutex if it was successfully locked
        if (result_try == SQLITE_OK) {
            sqlite3_mutex_leave(mutex);
        }

        // Only free dynamic mutexes
        if (type == SQLITE_MUTEX_FAST || type == SQLITE_MUTEX_RECURSIVE) {
            sqlite3_mutex_free(mutex);
        }
    }

    int threadsafe = sqlite3_threadsafe();
    if (threadsafe) {
        // Do something trivial
        (void)0;
    }

    return 0;
}