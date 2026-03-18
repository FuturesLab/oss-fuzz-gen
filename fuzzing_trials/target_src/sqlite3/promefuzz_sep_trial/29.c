// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_snprintf at sqlite3.c:19369:18 in sqlite3.h
// sqlite3_shutdown at sqlite3.c:171390:16 in sqlite3.h
// sqlite3_config at sqlite3.c:171444:16 in sqlite3.h
// sqlite3_hard_heap_limit64 at sqlite3.c:17198:26 in sqlite3.h
// sqlite3_hard_heap_limit64 at sqlite3.c:17198:26 in sqlite3.h
// sqlite3_config at sqlite3.c:171444:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdarg.h>

static void fuzz_sqlite3_snprintf(const uint8_t *Data, size_t Size) {
    if (Size < 3) return; // Ensure there's enough data for snprintf

    int bufferSize = Data[0] % 256 + 1; // Buffer size between 1 and 256
    char buffer[256];
    const char *format = "%s";
    size_t inputStrSize = Size - 1 < 255 ? Size - 1 : 255; // Limit input size to prevent overflow
    char inputStr[256];
    memcpy(inputStr, Data + 1, inputStrSize);
    inputStr[inputStrSize] = '\0'; // Ensure null-termination

    sqlite3_snprintf(bufferSize, buffer, format, inputStr);
}

int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    // Step 1: Call sqlite3_shutdown
    sqlite3_shutdown();

    // Step 2: Call sqlite3_config
    if (Size > 0) {
        int configOption = SQLITE_CONFIG_SINGLETHREAD; // Use a valid configuration option
        sqlite3_config(configOption);
    }

    // Step 3: Call sqlite3_hard_heap_limit64 twice
    if (Size > 8) {
        sqlite3_int64 limit = *((sqlite3_int64 *)(Data + 1)) % 1000000; // Limit between 0 and 1000000
        sqlite3_hard_heap_limit64(limit);
        sqlite3_hard_heap_limit64(limit / 2); // Call with a different limit
    }

    // Step 4: Call sqlite3_config again
    if (Size > 9) {
        int configOption = SQLITE_CONFIG_SINGLETHREAD; // Use a valid configuration option
        sqlite3_config(configOption);
    }

    // Step 5: Call sqlite3_snprintf
    fuzz_sqlite3_snprintf(Data, Size);

    return 0;
}