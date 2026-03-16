// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_vmprintf at sqlite3.c:19305:18 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_expanded_sql at sqlite3.c:80485:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdarg.h>

static sqlite3 *initialize_database() {
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return NULL;
    }
    return db;
}

static sqlite3_stmt *prepare_statement(sqlite3 *db, const char *sql) {
    sqlite3_stmt *stmt = NULL;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    return stmt;
}

static char *fuzz_vmprintf(const char *format, ...) {
    char *formatted_string = NULL;
    va_list args;
    va_start(args, format);
    formatted_string = sqlite3_vmprintf(format, args);
    va_end(args);
    return formatted_string;
}

int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    sqlite3 *db = initialize_database();
    if (!db) return 0;

    char *input_data = (char *)malloc(Size + 1);
    if (!input_data) {
        sqlite3_close(db);
        return 0;
    }

    memcpy(input_data, Data, Size);
    input_data[Size] = '\0';

    char *formatted_sql = fuzz_vmprintf("%s", input_data);
    free(input_data);

    if (!formatted_sql) {
        sqlite3_close(db);
        return 0;
    }

    sqlite3_stmt *stmt = prepare_statement(db, formatted_sql);
    if (stmt) {
        const char *errmsg = sqlite3_errmsg(db);
        if (errmsg) {
            char *expanded_sql = sqlite3_expanded_sql(stmt);
            if (expanded_sql) {
                sqlite3_free(expanded_sql);
            }
        }
        sqlite3_finalize(stmt);
    }

    sqlite3_free(formatted_sql);
    sqlite3_close(db);
    return 0;
}