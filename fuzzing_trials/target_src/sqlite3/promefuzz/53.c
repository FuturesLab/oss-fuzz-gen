// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_str_appendf at sqlite3.c:19465:17 in sqlite3.h
// sqlite3_str_appendall at sqlite3.c:19111:17 in sqlite3.h
// sqlite3_str_new at sqlite3.c:19257:25 in sqlite3.h
// sqlite3_str_finish at sqlite3.c:19172:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_str_free at sqlite3.c:19225:17 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <sqlite3.h>
#include <stdarg.h>
#include <string.h>

static void fuzz_sqlite3_str_appendf(sqlite3_str *pStr, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    const char *format = "%s";
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%.*s", (int)Size, Data);
    sqlite3_str_appendf(pStr, format, buffer);
}

static void fuzz_sqlite3_str_appendall(sqlite3_str *pStr, const uint8_t *Data, size_t Size) {
    char *nullTerminatedStr = (char *)malloc(Size + 1);
    if (!nullTerminatedStr) return;
    memcpy(nullTerminatedStr, Data, Size);
    nullTerminatedStr[Size] = '\0';
    sqlite3_str_appendall(pStr, nullTerminatedStr);
    free(nullTerminatedStr);
}

int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    sqlite3_str *pStr = sqlite3_str_new(db);

    if (!pStr) return 0;

    fuzz_sqlite3_str_appendf(pStr, Data, Size);
    fuzz_sqlite3_str_appendall(pStr, Data, Size);

    char *result = sqlite3_str_finish(pStr);
    if (result) {
        sqlite3_free(result);
    } else {
        sqlite3_str_free(pStr);
    }

    return 0;
}