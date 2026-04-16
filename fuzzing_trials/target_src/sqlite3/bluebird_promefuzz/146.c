#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "sqlite3.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static sqlite3 *initialize_database() {
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return NULL;
    }
    return db;
}

static sqlite3_stmt *prepare_statement(sqlite3 *db, const char *sql) {
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }
    return stmt;
}

int LLVMFuzzerTestOneInput_146(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    sqlite3 *db = initialize_database();
    if (!db) {
        return 0;
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS fuzz (id INTEGER PRIMARY KEY, data BLOB);";
    sqlite3_stmt *stmt = prepare_statement(db, sql);
    if (!stmt) {
        sqlite3_close(db);
        return 0;
    }

    sqlite3_step(stmt);
    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_finalize with sqlite3_step
    sqlite3_step(stmt);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR

    sql = "INSERT INTO fuzz (data) VALUES (?);";
    stmt = prepare_statement(db, sql);
    if (!stmt) {
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_blob(stmt, 1, Data, Size, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    sql = "SELECT data FROM fuzz WHERE id = 1;";
    stmt = prepare_statement(db, sql);
    if (!stmt) {
        sqlite3_close(db);
        return 0;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int bytes = sqlite3_column_bytes(stmt, 0);
        const void *blob = sqlite3_column_blob(stmt, 0);
        (void)blob;  // Use blob to avoid unused variable warning

        bytes = sqlite3_column_bytes(stmt, 0);
        blob = sqlite3_column_blob(stmt, 0);
        (void)blob;  // Use blob to avoid unused variable warning
    }

    int isExplain = sqlite3_stmt_isexplain(stmt);
    (void)isExplain;  // Use isExplain to avoid unused variable warning

    int resetResult = sqlite3_reset(stmt);
    (void)resetResult;  // Use resetResult to avoid unused variable warning

    int stepResult = sqlite3_step(stmt);
    (void)stepResult;  // Use stepResult to avoid unused variable warning

    const char *errMsg = sqlite3_errmsg(db);
    (void)errMsg;  // Use errMsg to avoid unused variable warning

    errMsg = sqlite3_errmsg(db);
    (void)errMsg;  // Use errMsg to avoid unused variable warning

    sqlite3_finalize(stmt);
    sqlite3_close(db);

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

    LLVMFuzzerTestOneInput_146(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
