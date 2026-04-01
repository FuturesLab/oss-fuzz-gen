// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_mutex_alloc at sqlite3.c:15870:27 in sqlite3.h
// sqlite3_mutex_enter at sqlite3.c:15902:17 in sqlite3.h
// sqlite3_mutex_held at sqlite3.c:15943:16 in sqlite3.h
// sqlite3_mutex_leave at sqlite3.c:15928:17 in sqlite3.h
// sqlite3_mutex_try at sqlite3.c:15913:16 in sqlite3.h
// sqlite3_mutex_leave at sqlite3.c:15928:17 in sqlite3.h
// sqlite3_mutex_free at sqlite3.c:15891:17 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

#define NUM_MUTEX_TYPES 15

static int get_mutex_type(const uint8_t *Data, size_t Size) {
    if (Size == 0) return SQLITE_MUTEX_FAST; // Default type if no data
    return Data[0] % NUM_MUTEX_TYPES;
}

static int map_mutex_type(int index) {
    switch (index) {
        case 0: return SQLITE_MUTEX_FAST;
        case 1: return SQLITE_MUTEX_RECURSIVE;
        case 2: return SQLITE_MUTEX_STATIC_MAIN;
        case 3: return SQLITE_MUTEX_STATIC_MEM;
        case 4: return SQLITE_MUTEX_STATIC_OPEN;
        case 5: return SQLITE_MUTEX_STATIC_PRNG;
        case 6: return SQLITE_MUTEX_STATIC_LRU;
        case 7: return SQLITE_MUTEX_STATIC_PMEM;
        case 8: return SQLITE_MUTEX_STATIC_APP1;
        case 9: return SQLITE_MUTEX_STATIC_APP2;
        case 10: return SQLITE_MUTEX_STATIC_APP3;
        case 11: return SQLITE_MUTEX_STATIC_VFS1;
        case 12: return SQLITE_MUTEX_STATIC_VFS2;
        case 13: return SQLITE_MUTEX_STATIC_VFS3;
        default: return SQLITE_MUTEX_FAST;
    }
}

int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Determine mutex type
    int index = get_mutex_type(Data, Size);
    int mutexType = map_mutex_type(index);

    // Allocate a mutex
    sqlite3_mutex *pMutex = sqlite3_mutex_alloc(mutexType);
    if (pMutex) {
        // Try to enter the mutex
        sqlite3_mutex_enter(pMutex);

        // Check if the mutex is held
        if (sqlite3_mutex_held(pMutex)) {
            // Attempt to leave the mutex
            sqlite3_mutex_leave(pMutex);
        }

        // Try to acquire the mutex without blocking
        int tryResult = sqlite3_mutex_try(pMutex);
        if (tryResult == SQLITE_OK) {
            // Leave the mutex if try was successful
            sqlite3_mutex_leave(pMutex);
        }

        // Free the mutex if it was dynamically allocated
        if (mutexType == SQLITE_MUTEX_FAST || mutexType == SQLITE_MUTEX_RECURSIVE) {
            sqlite3_mutex_free(pMutex);
        }
    }

    return 0;
}