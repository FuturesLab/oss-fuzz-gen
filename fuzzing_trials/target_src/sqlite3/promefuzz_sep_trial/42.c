// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_str_appendf at sqlite3.c:19465:17 in sqlite3.h
// sqlite3_str_appendall at sqlite3.c:19111:17 in sqlite3.h
// sqlite3_str_new at sqlite3.c:19257:25 in sqlite3.h
// sqlite3_str_value at sqlite3.c:19202:18 in sqlite3.h
// sqlite3_str_finish at sqlite3.c:19172:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdarg.h>

static void fuzz_sqlite3_str_appendf(sqlite3_str *pStr, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    // Create a format string by copying the input data
    char *format = (char *)malloc(Size + 1);
    if (!format) return;
    memcpy(format, Data, Size);
    format[Size] = '\0';

    // Append formatted data to the sqlite3_str object
    sqlite3_str_appendf(pStr, "%s", format);
    free(format);
}

static void fuzz_sqlite3_str_appendall(sqlite3_str *pStr, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    // Create a string by copying the input data
    char *str = (char *)malloc(Size + 1);
    if (!str) return;
    memcpy(str, Data, Size);
    str[Size] = '\0';

    // Append the entire string to the sqlite3_str object
    sqlite3_str_appendall(pStr, str);
    free(str);
}

int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    // Initialize a new sqlite3_str object
    sqlite3_str *pStr = sqlite3_str_new(NULL);
    if (!pStr) return 0;

    // Fuzz various functions with the input data
    fuzz_sqlite3_str_appendf(pStr, Data, Size);
    fuzz_sqlite3_str_appendall(pStr, Data, Size);

    // Retrieve the string value
    char *value = sqlite3_str_value(pStr);
    if (value) {
        // Use the value if needed (e.g., log, process, etc.)
    }

    // Finalize and clean up the sqlite3_str object
    char *finalStr = sqlite3_str_finish(pStr);
    if (finalStr) {
        sqlite3_free(finalStr);
    }

    return 0;
}