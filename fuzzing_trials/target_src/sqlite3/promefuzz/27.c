// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_reset at sqlite3.c:78461:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_reset at sqlite3.c:78461:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_reset at sqlite3.c:78461:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_column_int64 at sqlite3.c:79744:25 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static sqlite3 *create_in_memory_db() {
    sqlite3 *db = NULL;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return NULL;
    }
    return db;
}

static sqlite3_stmt *prepare_statement(sqlite3 *db) {
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value TEXT);"
                      "INSERT INTO test (value) VALUES (?);"
                      "SELECT * FROM test;";
    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }
    return stmt;
}

int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    sqlite3 *db = create_in_memory_db();
    if (!db) return 0;

    sqlite3_stmt *stmt = prepare_statement(db);
    if (!stmt) {
        sqlite3_close(db);
        return 0;
    }

    int rc = sqlite3_bind_text(stmt, 1, (const char *)Data, Size, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) goto cleanup;

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) goto cleanup;

    rc = sqlite3_reset(stmt);
    if (rc != SQLITE_OK) goto cleanup;

    rc = sqlite3_bind_text(stmt, 1, (const char *)Data, Size, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) goto cleanup;

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) goto cleanup;

    const char *errmsg = sqlite3_errmsg(db);
    (void)errmsg; // Suppress unused variable warning

    rc = sqlite3_reset(stmt);
    if (rc != SQLITE_OK) goto cleanup;

    rc = sqlite3_bind_text(stmt, 1, (const char *)Data, Size, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) goto cleanup;

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) goto cleanup;

    errmsg = sqlite3_errmsg(db);
    (void)errmsg; // Suppress unused variable warning

    rc = sqlite3_reset(stmt);
    if (rc != SQLITE_OK) goto cleanup;

    errmsg = sqlite3_errmsg(db);
    (void)errmsg; // Suppress unused variable warning

    rc = sqlite3_bind_text(stmt, 1, (const char *)Data, Size, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) goto cleanup;

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) goto cleanup;

    sqlite3_int64 val = sqlite3_column_int64(stmt, 0);
    (void)val; // Suppress unused variable warning

cleanup:
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}