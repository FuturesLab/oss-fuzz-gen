// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_create_collation at sqlite3.c:174754:16 in sqlite3.h
// sqlite3_value_type at sqlite3.c:78578:16 in sqlite3.h
// sqlite3_value_text at sqlite3.c:78560:33 in sqlite3.h
// sqlite3_result_int at sqlite3.c:78845:17 in sqlite3.h
// sqlite3_result_null at sqlite3.c:78859:17 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_collation_needed at sqlite3.c:174822:16 in sqlite3.h
// sqlite3_create_collation_v2 at sqlite3.c:174767:16 in sqlite3.h
// sqlite3_create_function at sqlite3.c:173127:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

static void collationNeededCallback(void *pArg, sqlite3 *db, int eTextRep, const char *zName) {
    // A simple callback that attempts to create a collation
    sqlite3_create_collation(db, zName, eTextRep, pArg, NULL);
}

static int customCompare(void *pArg, int len1, const void *str1, int len2, const void *str2) {
    // A simple comparison function for collation
    return strncmp((const char *)str1, (const char *)str2, len1 < len2 ? len1 : len2);
}

static void customFunction(sqlite3_context *context, int argc, sqlite3_value **argv) {
    // A simple custom function that returns the length of the first argument as text
    if (argc > 0 && sqlite3_value_type(argv[0]) == SQLITE_TEXT) {
        const unsigned char *text = sqlite3_value_text(argv[0]);
        sqlite3_result_int(context, strlen((const char *)text));
    } else {
        sqlite3_result_null(context);
    }
}

int LLVMFuzzerTestOneInput_126(const uint8_t *Data, size_t Size) {
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Register the collation needed callback
    sqlite3_collation_needed(db, NULL, collationNeededCallback);

    // Register a custom collation
    sqlite3_create_collation_v2(db, "custom_collation", SQLITE_UTF8, NULL, customCompare, NULL);

    // Register a custom function
    sqlite3_create_function(db, "custom_function", 1, SQLITE_UTF8, NULL, customFunction, NULL, NULL);

    // Prepare a dummy SQL statement
    char *sql = "SELECT custom_function('test') COLLATE custom_collation;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
    return 0;
}