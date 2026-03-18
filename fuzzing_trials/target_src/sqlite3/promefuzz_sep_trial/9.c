// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_stricmp at sqlite3.c:22312:16 in sqlite3.h
// sqlite3_strnicmp at sqlite3.c:22339:16 in sqlite3.h
// sqlite3_strglob at sqlite3.c:119294:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

static int safe_stricmp(const char *a, const char *b) {
    if (!a && !b) return 0;
    if (!a) return -1;
    if (!b) return 1;
    return sqlite3_stricmp(a, b);
}

static int safe_strnicmp(const char *a, const char *b, int n) {
    if (!a && !b) return 0;
    if (!a) return -1;
    if (!b) return 1;
    return sqlite3_strnicmp(a, b, n);
}

static int safe_strglob(const char *pattern, const char *str) {
    if (!pattern && !str) return 0;
    if (!pattern) return -1;
    if (!str) return 1;
    return sqlite3_strglob(pattern, str);
}

int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    const char *str1 = (const char *)Data;
    const char *str2 = (const char *)(Data + 1);

    // Ensure null-terminated strings for safety
    char buf1[256], buf2[256];
    size_t len1 = Size > 255 ? 255 : Size;
    size_t len2 = Size > 254 ? 254 : Size - 1;

    strncpy(buf1, str1, len1);
    buf1[len1] = '\0';

    strncpy(buf2, str2, len2);
    buf2[len2] = '\0';

    // Invoke functions in specified order
    safe_stricmp(buf1, buf2);
    safe_stricmp(buf2, buf1);
    safe_stricmp(buf1, buf1);
    safe_strnicmp(buf1, buf2, (int)(Size % 256));
    safe_stricmp(buf2, buf2);
    safe_stricmp(buf1, buf2);
    safe_stricmp(buf2, buf1);
    safe_strglob(buf1, buf2);
    safe_strglob(buf2, buf1);
    safe_stricmp(buf1, buf1);

    return 0;
}