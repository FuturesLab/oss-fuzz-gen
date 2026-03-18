// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_str_new at sqlite3.c:19257:25 in sqlite3.h
// sqlite3_str_append at sqlite3.c:19094:17 in sqlite3.h
// sqlite3_str_appendchar at sqlite3.c:19066:17 in sqlite3.h
// sqlite3_str_truncate at sqlite3.c:19194:17 in sqlite3.h
// sqlite3_str_length at sqlite3.c:19189:16 in sqlite3.h
// sqlite3_str_errcode at sqlite3.c:19184:16 in sqlite3.h
// sqlite3_str_reset at sqlite3.c:19211:17 in sqlite3.h
// sqlite3_str_finish at sqlite3.c:19172:18 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_80(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a new sqlite3_str object
    sqlite3_str *str = sqlite3_str_new(NULL);

    if (str == NULL) {
        return 0;
    }

    // Fuzz sqlite3_str_append
    sqlite3_str_append(str, (const char*)Data, (int)Size);

    // Fuzz sqlite3_str_appendchar
    if (Size > 1) {
        char C = (char)Data[0];
        int N = (int)Data[1];
        sqlite3_str_appendchar(str, N, C);
    }

    // Fuzz sqlite3_str_truncate
    if (Size > 2) {
        int N = (int)Data[2];
        sqlite3_str_truncate(str, N);
    }

    // Check the length of the string
    int length = sqlite3_str_length(str);

    // Check the error code
    int errcode = sqlite3_str_errcode(str);

    // Reset the string
    sqlite3_str_reset(str);

    // Clean up by finalizing the sqlite3_str object
    char *finalized_str = sqlite3_str_finish(str);
    if (finalized_str) {
        free(finalized_str);
    }

    return 0;
}