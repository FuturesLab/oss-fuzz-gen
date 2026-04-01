// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_blob at sqlite3.c:80082:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_column_bytes at sqlite3.c:79724:16 in sqlite3.h
// sqlite3_column_blob at sqlite3.c:79714:24 in sqlite3.h
// sqlite3_column_bytes at sqlite3.c:79724:16 in sqlite3.h
// sqlite3_column_blob at sqlite3.c:79714:24 in sqlite3.h
// sqlite3_stmt_isexplain at sqlite3.c:80364:16 in sqlite3.h
// sqlite3_reset at sqlite3.c:78461:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
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

int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db = initialize_database();
    if (!db) return 0;

    const char *sql = "CREATE TABLE IF NOT EXISTS fuzz (id INTEGER PRIMARY KEY, data BLOB);";
    sqlite3_stmt *stmt = prepare_statement(db, sql);
    if (!stmt) {
        sqlite3_close(db);
        return 0;
    }

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

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