#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "sqlite3.h"
#include <stdarg.h>

static sqlite3 *initialize_db() {
    sqlite3 *db = NULL;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }
    return db;
}

static void cleanup_db(sqlite3 *db) {
    if (db) {
        sqlite3_close(db);
    }
}

static char *custom_vmprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char *result = sqlite3_vmprintf(format, args);
    va_end(args);
    return result;
}

int LLVMFuzzerTestOneInput_245(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    sqlite3 *db = initialize_db();
    if (!db) {
        return 0;
    }

    // Use custom_vmprintf to create a format string
    char *formatted_str = custom_vmprintf("%.*s", (int)Size, Data);
    if (!formatted_str) {
        cleanup_db(db);
        return 0;
    }

    // Prepare a statement using sqlite3_prepare_v2
    sqlite3_stmt *stmt = NULL;
    const char *tail = NULL;
    int rc = sqlite3_prepare_v2(db, formatted_str, -1, &stmt, &tail);
    if (rc != SQLITE_OK) {
        const char *err_msg = sqlite3_errmsg(db);
        fprintf(stderr, "SQL error: %s\n", err_msg);
    } else {
        // If the statement is prepared successfully, get the expanded SQL
        char *expanded_sql = sqlite3_expanded_sql(stmt);
        if (expanded_sql) {
            sqlite3_free(expanded_sql);
        }
        sqlite3_finalize(stmt);
    }

    // Free the formatted string

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_prepare_v2 to sqlite3_open16
    int ret_sqlite3_open16_esefq = sqlite3_open16(NULL, &db);
    if (ret_sqlite3_open16_esefq < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    sqlite3_free(formatted_str);

    // Cleanup
    cleanup_db(db);
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

    LLVMFuzzerTestOneInput_245(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
