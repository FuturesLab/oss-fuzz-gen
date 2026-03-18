// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open16 at sqlite3.c:174715:16 in sqlite3.h
// sqlite3_create_function16 at sqlite3.c:173171:16 in sqlite3.h
// sqlite3_prepare16_v3 at sqlite3.c:132712:16 in sqlite3.h
// sqlite3_prepare16_v2 at sqlite3.c:132700:16 in sqlite3.h
// sqlite3_column_name16 at sqlite3.c:79887:24 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_errmsg16 at sqlite3.c:173785:24 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "sqlite3.h"

static void dummy_function(sqlite3_context *context, int argc, sqlite3_value **argv) {
    // This is a dummy function to be used with sqlite3_create_function16
}

int LLVMFuzzerTestOneInput_121(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Ensure there's enough data to work with

    // Prepare a UTF-16 filename from input data, ensuring it's null-terminated
    size_t utf16_len = Size / 2;
    uint16_t *utf16_filename = (uint16_t *)malloc((utf16_len + 1) * sizeof(uint16_t));
    if (!utf16_filename) return 0;
    memcpy(utf16_filename, Data, utf16_len * sizeof(uint16_t));
    utf16_filename[utf16_len] = 0; // Null-terminate

    sqlite3 *db = NULL;

    // Fuzz sqlite3_open16
    int rc = sqlite3_open16(utf16_filename, &db);
    if (rc == SQLITE_OK) {
        // Prepare a UTF-16 function name from input data, ensuring it's null-terminated
        size_t func_name_offset = (utf16_len > 1) ? 1 : 0;
        size_t func_name_len = (utf16_len - func_name_offset) / 2;
        uint16_t *utf16_function_name = (uint16_t *)malloc((func_name_len + 1) * sizeof(uint16_t));
        if (utf16_function_name) {
            memcpy(utf16_function_name, Data + func_name_offset * sizeof(uint16_t), func_name_len * sizeof(uint16_t));
            utf16_function_name[func_name_len] = 0; // Null-terminate

            // Fuzz sqlite3_create_function16
            sqlite3_create_function16(db, utf16_function_name, 1, SQLITE_UTF16, NULL, dummy_function, NULL, NULL);

            free(utf16_function_name);
        }

        // Fuzz sqlite3_prepare16_v3
        sqlite3_stmt *stmt = NULL;
        const void *pzTail = NULL;
        sqlite3_prepare16_v3(db, utf16_filename, (int)Size, 0, &stmt, &pzTail);

        // Fuzz sqlite3_prepare16_v2
        sqlite3_prepare16_v2(db, utf16_filename, (int)Size, &stmt, &pzTail);

        // If a statement was prepared, fuzz sqlite3_column_name16
        if (stmt) {
            sqlite3_column_name16(stmt, 0);
            sqlite3_finalize(stmt);
        }

        // Fuzz sqlite3_errmsg16
        sqlite3_errmsg16(db);

        sqlite3_close(db);
    }

    free(utf16_filename);
    return 0;
}