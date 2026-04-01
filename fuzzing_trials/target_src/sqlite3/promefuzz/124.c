// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_str_new at sqlite3.c:19257:25 in sqlite3.h
// sqlite3_str_append at sqlite3.c:19094:17 in sqlite3.h
// sqlite3_str_appendf at sqlite3.c:19465:17 in sqlite3.h
// sqlite3_stricmp at sqlite3.c:22312:16 in sqlite3.h
// sqlite3_strglob at sqlite3.c:119294:16 in sqlite3.h
// sqlite3_strnicmp at sqlite3.c:22339:16 in sqlite3.h
// sqlite3_strlike at sqlite3.c:119308:16 in sqlite3.h
// sqlite3_str_finish at sqlite3.c:19172:18 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <limits.h>

static sqlite3_str* create_sqlite3_str() {
    sqlite3 *db = NULL;
    return sqlite3_str_new(db);
}

static void fuzz_sqlite3_str_append(sqlite3_str* pStr, const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        int N = Size < INT_MAX ? (int)Size : INT_MAX;
        sqlite3_str_append(pStr, (const char*)Data, N);
    }
}

static void fuzz_sqlite3_str_appendf(sqlite3_str* pStr, const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        // Ensure the data is null-terminated for safe string operations
        char *buffer = strndup((const char*)Data, Size);
        if (buffer) {
            char format[] = "%s";
            sqlite3_str_appendf(pStr, format, buffer);
            free(buffer);
        }
    }
}

static void fuzz_sqlite3_stricmp(const uint8_t *Data, size_t Size) {
    if (Size > 1) {
        size_t mid = Size / 2;
        char *str1 = strndup((const char*)Data, mid);
        char *str2 = strndup((const char*)Data + mid, Size - mid);
        if (str1 && str2) {
            sqlite3_stricmp(str1, str2);
        }
        free(str1);
        free(str2);
    }
}

static void fuzz_sqlite3_strglob(const uint8_t *Data, size_t Size) {
    if (Size > 1) {
        size_t mid = Size / 2;
        char *pattern = strndup((const char*)Data, mid);
        char *str = strndup((const char*)Data + mid, Size - mid);
        if (pattern && str) {
            sqlite3_strglob(pattern, str);
        }
        free(pattern);
        free(str);
    }
}

static void fuzz_sqlite3_strnicmp(const uint8_t *Data, size_t Size) {
    if (Size > 2) {
        size_t mid = Size / 3;
        char *str1 = strndup((const char*)Data, mid);
        char *str2 = strndup((const char*)Data + mid, mid);
        if (str1 && str2) {
            int N = *(Data + 2 * mid) % 100; // Limit N to a reasonable number
            sqlite3_strnicmp(str1, str2, N);
        }
        free(str1);
        free(str2);
    }
}

static void fuzz_sqlite3_strlike(const uint8_t *Data, size_t Size) {
    if (Size > 2) {
        size_t mid = Size / 3;
        char *pattern = strndup((const char*)Data, mid);
        char *str = strndup((const char*)Data + mid, mid);
        if (pattern && str) {
            unsigned int esc = *(Data + 2 * mid);
            sqlite3_strlike(pattern, str, esc);
        }
        free(pattern);
        free(str);
    }
}

int LLVMFuzzerTestOneInput_124(const uint8_t *Data, size_t Size) {
    sqlite3_str* pStr = create_sqlite3_str();

    fuzz_sqlite3_str_append(pStr, Data, Size);
    fuzz_sqlite3_str_appendf(pStr, Data, Size);
    fuzz_sqlite3_stricmp(Data, Size);
    fuzz_sqlite3_strglob(Data, Size);
    fuzz_sqlite3_strnicmp(Data, Size);
    fuzz_sqlite3_strlike(Data, Size);

    sqlite3_str_finish(pStr);
    return 0;
}