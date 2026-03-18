// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_stricmp at sqlite3.c:22312:16 in sqlite3.h
// sqlite3_strnicmp at sqlite3.c:22339:16 in sqlite3.h
// sqlite3_strglob at sqlite3.c:119294:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "sqlite3.h"

static int safe_stricmp(const char *a, const char *b) {
    if (a == NULL || b == NULL) {
        return (a == b) ? 0 : (a == NULL ? -1 : 1);
    }
    return sqlite3_stricmp(a, b);
}

static int safe_strnicmp(const char *a, const char *b, int n) {
    if (a == NULL || b == NULL) {
        return (a == b) ? 0 : (a == NULL ? -1 : 1);
    }
    return sqlite3_strnicmp(a, b, n);
}

static int safe_strglob(const char *glob, const char *str) {
    if (glob == NULL || str == NULL) {
        return (glob == str) ? 0 : (glob == NULL ? -1 : 1);
    }
    return sqlite3_strglob(glob, str);
}

int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    if (Size < 3) return 0; // Ensure there is enough data to split

    size_t part_size = Size / 3;
    const char *str1 = (const char *)Data;
    const char *str2 = (const char *)(Data + part_size);
    const char *str3 = (const char *)(Data + 2 * part_size);

    // Ensure null-termination within bounds
    char *null_terminated_str1 = strndup(str1, part_size);
    char *null_terminated_str2 = strndup(str2, part_size);
    char *null_terminated_str3 = strndup(str3, Size - 2 * part_size);

    // Invoke sqlite3_stricmp multiple times
    safe_stricmp(null_terminated_str1, null_terminated_str2);
    safe_stricmp(null_terminated_str2, null_terminated_str3);
    safe_stricmp(null_terminated_str3, null_terminated_str1);

    // Invoke sqlite3_strnicmp
    safe_strnicmp(null_terminated_str1, null_terminated_str2, 10);

    // Invoke sqlite3_stricmp again
    safe_stricmp(null_terminated_str1, null_terminated_str2);
    safe_stricmp(null_terminated_str2, null_terminated_str3);
    safe_stricmp(null_terminated_str3, null_terminated_str1);

    // Invoke sqlite3_strglob
    safe_strglob(null_terminated_str1, null_terminated_str2);
    safe_strglob(null_terminated_str2, null_terminated_str3);

    // Final call to sqlite3_stricmp
    safe_stricmp(null_terminated_str1, null_terminated_str2);

    // Cleanup
    free(null_terminated_str1);
    free(null_terminated_str2);
    free(null_terminated_str3);

    return 0;
}