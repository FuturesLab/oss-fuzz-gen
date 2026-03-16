#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include <stdlib.h>
#include "stdio.h"
#include "sqlite3.h"
#include "stdint.h"
#include "stddef.h"
#include "string.h"

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

int LLVMFuzzerTestOneInput_357(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_close to sqlite3_errmsg

    const char* ret_sqlite3_errmsg_cqbhp = sqlite3_errmsg(db);
    if (ret_sqlite3_errmsg_cqbhp == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sqlite3_close(db);
    return 0;
}