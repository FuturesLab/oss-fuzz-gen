// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_malloc64 at sqlite3.c:17383:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_free_table at sqlite3.c:141881:17 in sqlite3.h
// sqlite3_free_filename at sqlite3.c:175855:17 in sqlite3.h
// sqlite3_vmprintf at sqlite3.c:19305:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_malloc at sqlite3.c:17377:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdarg.h>

static void fuzz_sqlite3_malloc64(sqlite3_uint64 size) {
    void *ptr = sqlite3_malloc64(size);
    if (ptr) {
        sqlite3_free(ptr);
    }
}

static void fuzz_sqlite3_free(void *ptr) {
    sqlite3_free(ptr);
}

static void fuzz_sqlite3_free_table(char **result) {
    if (result && *result) {
        sqlite3_free_table(result);
    }
}

static void fuzz_sqlite3_free_filename(sqlite3_filename filename) {
    sqlite3_free_filename(filename);
}

static void fuzz_sqlite3_mprintf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char *result = sqlite3_vmprintf(fmt, args);
    va_end(args);
    if (result) {
        sqlite3_free(result);
    }
}

static void fuzz_sqlite3_malloc(int size) {
    void *ptr = sqlite3_malloc(size);
    if (ptr) {
        sqlite3_free(ptr);
    }
}

int LLVMFuzzerTestOneInput_115(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(sqlite3_uint64) + sizeof(int)) {
        return 0;
    }

    sqlite3_uint64 malloc64_size;
    int malloc_size;
    const char *fmt = "%s";

    malloc64_size = *((sqlite3_uint64*)Data);
    Data += sizeof(sqlite3_uint64);
    Size -= sizeof(sqlite3_uint64);

    malloc_size = *((int*)Data);
    Data += sizeof(int);
    Size -= sizeof(int);

    fuzz_sqlite3_malloc64(malloc64_size);
    fuzz_sqlite3_free(NULL);

    // Ensure dummy_result is safely initialized with a valid pointer
    char *dummy_result[2] = { NULL, NULL };
    fuzz_sqlite3_free_table(dummy_result);

    fuzz_sqlite3_free_filename(NULL);
    fuzz_sqlite3_mprintf(fmt, "test");
    fuzz_sqlite3_malloc(malloc_size);

    return 0;
}