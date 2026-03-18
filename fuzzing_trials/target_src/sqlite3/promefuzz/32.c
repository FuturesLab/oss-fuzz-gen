// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_config at sqlite3.c:171444:16 in sqlite3.h
// sqlite3_hard_heap_limit64 at sqlite3.c:17198:26 in sqlite3.h
// sqlite3_snprintf at sqlite3.c:19369:18 in sqlite3.h
// sqlite3_shutdown at sqlite3.c:171390:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

static void fuzz_sqlite3_config() {
    // Example configuration option, SQLITE_CONFIG_SINGLETHREAD is 1
    sqlite3_config(1);
}

static void fuzz_sqlite3_hard_heap_limit64() {
    sqlite3_int64 limit = 1024 * 1024; // 1MB limit
    sqlite3_hard_heap_limit64(limit);
}

static void fuzz_sqlite3_snprintf() {
    char buffer[100];
    const char *format = "Formatted number: %d";
    sqlite3_snprintf(sizeof(buffer), buffer, format, 42);
}

int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Invoke sqlite3_shutdown
    sqlite3_shutdown();

    // Fuzz sqlite3_config
    fuzz_sqlite3_config();

    // Fuzz sqlite3_hard_heap_limit64
    fuzz_sqlite3_hard_heap_limit64();
    fuzz_sqlite3_hard_heap_limit64();

    // Fuzz sqlite3_config again
    fuzz_sqlite3_config();

    // Fuzz sqlite3_snprintf
    fuzz_sqlite3_snprintf();

    return 0;
}