// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_status at sqlite3.c:10769:16 in sqlite3.h
// sqlite3_memory_highwater at sqlite3.c:17269:26 in sqlite3.h
// sqlite3_status64 at sqlite3.c:10744:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_db_status64 at sqlite3.c:10813:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_memory_used at sqlite3.c:17258:26 in sqlite3.h
// sqlite3_soft_heap_limit64 at sqlite3.c:17156:26 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

static void fuzz_sqlite3_status(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 3) return; // Ensure enough data for op, resetFlag, and two int pointers

    int op = *((int*)Data);
    int resetFlag = *((int*)(Data + sizeof(int)));
    int current, highwater;

    int rc = sqlite3_status(op, &current, &highwater, resetFlag);
    if (rc != SQLITE_OK) {
        // Handle error
    }
}

static void fuzz_sqlite3_memory_highwater(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return; // Ensure enough data for resetFlag

    int resetFlag = *((int*)Data);
    sqlite3_int64 highwater = sqlite3_memory_highwater(resetFlag);
    (void)highwater; // Use highwater in some way to avoid compiler warnings
}

static void fuzz_sqlite3_status64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) + sizeof(sqlite3_int64) * 2) return; // Ensure enough data

    int op = *((int*)Data);
    int resetFlag = *((int*)(Data + sizeof(int)));
    sqlite3_int64 current, highwater;

    int rc = sqlite3_status64(op, &current, &highwater, resetFlag);
    if (rc != SQLITE_OK) {
        // Handle error
    }
}

static void fuzz_sqlite3_db_status64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) + sizeof(sqlite3_int64) * 2 + sizeof(int)) return;

    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return; // Handle error if database cannot be opened
    }

    int op = *((int*)Data);
    sqlite3_int64 current, highwater;
    int resetFlag = *((int*)(Data + sizeof(int) + sizeof(sqlite3_int64) * 2));

    int rc = sqlite3_db_status64(db, op, &current, &highwater, resetFlag);
    if (rc != SQLITE_OK) {
        // Handle error
    }

    sqlite3_close(db);
}

static void fuzz_sqlite3_memory_used() {
    sqlite3_int64 memoryUsed = sqlite3_memory_used();
    (void)memoryUsed; // Use memoryUsed in some way to avoid compiler warnings
}

static void fuzz_sqlite3_soft_heap_limit64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(sqlite3_int64)) return;

    sqlite3_int64 N = *((sqlite3_int64*)Data);
    sqlite3_int64 previousLimit = sqlite3_soft_heap_limit64(N);
    (void)previousLimit; // Use previousLimit in some way to avoid compiler warnings
}

int LLVMFuzzerTestOneInput_138(const uint8_t *Data, size_t Size) {
    fuzz_sqlite3_status(Data, Size);
    fuzz_sqlite3_memory_highwater(Data, Size);
    fuzz_sqlite3_status64(Data, Size);
    fuzz_sqlite3_db_status64(Data, Size);
    fuzz_sqlite3_memory_used();
    fuzz_sqlite3_soft_heap_limit64(Data, Size);
    return 0;
}