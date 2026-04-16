#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "sqlite3.h"

static void dummy_function(sqlite3_context *context, int argc, sqlite3_value **argv) {
    // This is a dummy function to be used with sqlite3_create_function16
}

int LLVMFuzzerTestOneInput_353(const uint8_t *Data, size_t Size) {
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

    LLVMFuzzerTestOneInput_353(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
