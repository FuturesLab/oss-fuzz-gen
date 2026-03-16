// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_str_new at sqlite3.c:19257:25 in sqlite3.h
// sqlite3_str_reset at sqlite3.c:19211:17 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_str_appendchar at sqlite3.c:19066:17 in sqlite3.h
// sqlite3_str_errcode at sqlite3.c:19184:16 in sqlite3.h
// sqlite3_str_truncate at sqlite3.c:19194:17 in sqlite3.h
// sqlite3_str_length at sqlite3.c:19189:16 in sqlite3.h
// sqlite3_str_append at sqlite3.c:19094:17 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

static sqlite3_str* create_sqlite3_str() {
    sqlite3 *db = NULL;
    sqlite3_str *str = sqlite3_str_new(db);
    return str;
}

static void cleanup_sqlite3_str(sqlite3_str *str) {
    if (str) {
        sqlite3_str_reset(str);
        sqlite3_free(str);
    }
}

int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size < 3) return 0;

    sqlite3_str *str = create_sqlite3_str();
    if (!str) return 0;

    int N = Data[0];
    char C = (char)Data[1];
    int truncate_length = Data[2] % (N + 1);

    // Test sqlite3_str_appendchar
    sqlite3_str_appendchar(str, N, C);

    // Test sqlite3_str_errcode
    int errcode = sqlite3_str_errcode(str);

    // Test sqlite3_str_truncate
    sqlite3_str_truncate(str, truncate_length);

    // Test sqlite3_str_length
    int length = sqlite3_str_length(str);

    // Test sqlite3_str_append
    if (Size > 3) {
        const char *append_str = (const char *)(Data + 3);
        int append_length = Size - 3;
        sqlite3_str_append(str, append_str, append_length);
    }

    // Cleanup
    cleanup_sqlite3_str(str);

    return 0;
}