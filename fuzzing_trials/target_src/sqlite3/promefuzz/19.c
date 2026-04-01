// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_str_new at sqlite3.c:19257:25 in sqlite3.h
// sqlite3_str_appendf at sqlite3.c:19465:17 in sqlite3.h
// sqlite3_str_appendf at sqlite3.c:19465:17 in sqlite3.h
// sqlite3_str_finish at sqlite3.c:19172:18 in sqlite3.h
// sqlite3_str_finish at sqlite3.c:19172:18 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

static int open_database(sqlite3 **db) {
    return sqlite3_open("./dummy_file", db);
}

static sqlite3_str* create_dynamic_string(sqlite3 *db) {
    return sqlite3_str_new(db);
}

int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    sqlite3_str *str1 = NULL, *str2 = NULL;
    char *result1 = NULL, *result2 = NULL;

    if (open_database(&db) != SQLITE_OK) {
        return 0;
    }

    str1 = create_dynamic_string(db);
    str2 = create_dynamic_string(db);

    if (str1 && Size > 0) {
        sqlite3_str_appendf(str1, "%.*s", (int)Size, Data);
    }
    if (str2 && Size > 0) {
        sqlite3_str_appendf(str2, "%.*s", (int)Size, Data);
    }

    result1 = sqlite3_str_finish(str1);
    result2 = sqlite3_str_finish(str2);

    sqlite3_close(db);

    sqlite3_free(result1);
    sqlite3_free(result2);

    return 0;
}