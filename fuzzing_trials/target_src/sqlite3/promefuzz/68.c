// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_create_collation at sqlite3.c:174754:16 in sqlite3.h
// sqlite3_result_null at sqlite3.c:78859:17 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_create_collation16 at sqlite3.c:174792:16 in sqlite3.h
// sqlite3_collation_needed at sqlite3.c:174822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_create_collation_v2 at sqlite3.c:174767:16 in sqlite3.h
// sqlite3_create_function at sqlite3.c:173127:16 in sqlite3.h
// sqlite3_create_module_v2 at sqlite3.c:145711:16 in sqlite3.h
// sqlite3_create_collation at sqlite3.c:174754:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

static int dummy_compare(void* pArg, int len1, const void* str1, int len2, const void* str2) {
    return memcmp(str1, str2, len1 < len2 ? len1 : len2);
}

static void dummy_collation_needed(void* pArg, sqlite3* db, int eTextRep, const char* zName) {
    sqlite3_create_collation(db, zName, eTextRep, NULL, dummy_compare);
}

static void dummy_function(sqlite3_context* context, int argc, sqlite3_value** argv) {
    sqlite3_result_null(context);
}

static int dummy_module_create(sqlite3* db, void* pAux, int argc, const char* const* argv, sqlite3_vtab** ppVTab, char** pzErr) {
    return SQLITE_OK;
}

static sqlite3_module dummy_module = {
    1,
    dummy_module_create,
    dummy_module_create,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

int LLVMFuzzerTestOneInput_68(const uint8_t *Data, size_t Size) {
    if (Size < 4) { // Ensure enough data for UTF-16
        return 0;
    }

    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    void* pArg = NULL;
    int eTextRep = SQLITE_UTF8;

    // Ensure UTF-16 data is properly sized and null-terminated
    size_t utf16Size = (Size / 2) * 2; // Ensure it's an even number
    uint16_t* zName16 = (uint16_t*)malloc(utf16Size + 2); // Extra space for null terminator
    if (!zName16) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(zName16, Data, utf16Size);
    zName16[utf16Size / 2] = 0; // Null-terminate the UTF-16 string

    // Fuzzing sqlite3_create_collation16
    if (utf16Size >= 4) { // Ensure there is at least 2 UTF-16 characters
        sqlite3_create_collation16(db, zName16, eTextRep, pArg, dummy_compare);
    }

    // Fuzzing sqlite3_collation_needed
    sqlite3_collation_needed(db, pArg, dummy_collation_needed);

    // Fuzzing sqlite3_create_collation_v2
    char* zName = (char*)malloc(Size + 1); // Allocate space for null-terminated string
    if (!zName) {
        free(zName16);
        sqlite3_close(db);
        return 0;
    }
    memcpy(zName, Data, Size);
    zName[Size] = '\0'; // Null-terminate the string
    void (*xDestroy)(void*) = NULL;
    sqlite3_create_collation_v2(db, zName, eTextRep, pArg, dummy_compare, xDestroy);

    // Fuzzing sqlite3_create_function
    sqlite3_create_function(db, zName, -1, eTextRep, pArg, dummy_function, NULL, NULL);

    // Fuzzing sqlite3_create_module_v2
    void (*xDestroyModule)(void*) = NULL;
    sqlite3_create_module_v2(db, zName, &dummy_module, pArg, xDestroyModule);

    // Fuzzing sqlite3_create_collation
    sqlite3_create_collation(db, zName, eTextRep, pArg, dummy_compare);

    free(zName);
    free(zName16);
    sqlite3_close(db);
    return 0;
}