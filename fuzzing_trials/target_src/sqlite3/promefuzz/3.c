// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_column_count at sqlite3.c:79599:16 in sqlite3.h
// sqlite3_column_type at sqlite3.c:79770:16 in sqlite3.h
// sqlite3_column_name at sqlite3.c:79883:24 in sqlite3.h
// sqlite3_column_text at sqlite3.c:79749:33 in sqlite3.h
// sqlite3_column_bytes at sqlite3.c:79724:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
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

static void execute_sqlite_fuzzing(sqlite3 *db, const char *sql) {
    sqlite3_stmt *stmt = NULL;
    const char *pzTail = NULL;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &pzTail);
    if (rc != SQLITE_OK) {
        const char *errmsg = sqlite3_errmsg(db);
        (void)errmsg;  // Suppress unused variable warning
        return;
    }

    rc = sqlite3_step(stmt);
    rc = sqlite3_step(stmt);  // Call sqlite3_step twice as required

    int column_count = sqlite3_column_count(stmt);
    for (int i = 0; i < column_count; i++) {
        int col_type = sqlite3_column_type(stmt, i);
        const char *col_name = sqlite3_column_name(stmt, i);
        const unsigned char *col_text = sqlite3_column_text(stmt, i);
        int col_bytes = sqlite3_column_bytes(stmt, i);

        (void)col_type;  // Suppress unused variable warning
        (void)col_name;
        (void)col_text;
        (void)col_bytes;
    }

    sqlite3_finalize(stmt);
}

int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Initialize SQLite
    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Copy input data to a null-terminated string
    char *sql = (char *)malloc(Size + 1);
    if (!sql) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, Data, Size);
    sql[Size] = '\0';

    // Execute fuzzing with the given SQL
    execute_sqlite_fuzzing(db, sql);

    // Cleanup
    free(sql);
    sqlite3_close(db);
    return 0;
}