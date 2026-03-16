// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_memory_used at sqlite3.c:17258:26 in sqlite3.h
// sqlite3_status at sqlite3.c:10769:16 in sqlite3.h
// sqlite3_soft_heap_limit64 at sqlite3.c:17156:26 in sqlite3.h
// sqlite3_status64 at sqlite3.c:10744:16 in sqlite3.h
// sqlite3_memory_highwater at sqlite3.c:17269:26 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

static void fuzz_sqlite3_memory_used() {
    sqlite3_int64 memoryUsed = sqlite3_memory_used();
    (void)memoryUsed; // Suppress unused variable warning
}

static void fuzz_sqlite3_status(int op) {
    int current = 0;
    int highwater = 0;
    int result = sqlite3_status(op, &current, &highwater, 1);
    (void)result; // Suppress unused variable warning
}

static void fuzz_sqlite3_soft_heap_limit64(sqlite3_int64 limit) {
    sqlite3_int64 oldLimit = sqlite3_soft_heap_limit64(limit);
    (void)oldLimit; // Suppress unused variable warning
}

static void fuzz_sqlite3_status64(int op) {
    sqlite3_int64 current = 0;
    sqlite3_int64 highwater = 0;
    int result = sqlite3_status64(op, &current, &highwater, 1);
    (void)result; // Suppress unused variable warning
}

static void fuzz_sqlite3_memory_highwater() {
    sqlite3_int64 highwater = sqlite3_memory_highwater(1);
    (void)highwater; // Suppress unused variable warning
}

int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) + sizeof(sqlite3_int64)) {
        return 0;
    }

    int op = *((int *)Data);
    sqlite3_int64 limit = *((sqlite3_int64 *)(Data + sizeof(int)));

    fuzz_sqlite3_memory_used();
    fuzz_sqlite3_status(op);
    fuzz_sqlite3_soft_heap_limit64(limit);
    fuzz_sqlite3_status64(op);
    fuzz_sqlite3_memory_highwater();

    return 0;
}