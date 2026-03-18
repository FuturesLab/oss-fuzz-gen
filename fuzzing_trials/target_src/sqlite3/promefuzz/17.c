// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_vmprintf at sqlite3.c:19305:18 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_expanded_sql at sqlite3.c:80485:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
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

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db = initialize_db();
    if (!db) return 0;

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
    sqlite3_free(formatted_str);

    // Cleanup
    cleanup_db(db);
    return 0;
}