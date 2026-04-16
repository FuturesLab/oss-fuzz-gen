#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "sqlite3.h"
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

int LLVMFuzzerTestOneInput_429(const uint8_t *Data, size_t Size) {
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
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_429(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
