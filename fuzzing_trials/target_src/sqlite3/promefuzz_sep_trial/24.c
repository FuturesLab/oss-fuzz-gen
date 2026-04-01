// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
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

static void prepareDummyDatabase(sqlite3 *db) {
    char *errMsg = 0;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value TEXT);";
    sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (errMsg) {
        sqlite3_free(errMsg);
    }
}

static sqlite3_stmt* prepareStatement(sqlite3 *db) {
    const char *sql = "INSERT INTO test (value) VALUES (?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        return NULL;
    }
    return stmt;
}

int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Ensure there's enough data for meaningful operations

    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *errMsg = 0;

    // Open an in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Prepare the database environment
    prepareDummyDatabase(db);

    // Prepare a statement
    stmt = prepareStatement(db);
    if (!stmt) {
        sqlite3_close(db);
        return 0;
    }

    // Bind, execute, reset, and retrieve error messages
    int rc;
    const int bindIndex = 1;
    const char *text = (const char *)Data;
    int textLength = (int)Size;

    rc = sqlite3_bind_text(stmt, bindIndex, text, textLength, SQLITE_TRANSIENT);
    rc = sqlite3_step(stmt);
    rc = sqlite3_reset(stmt);

    rc = sqlite3_bind_text(stmt, bindIndex, text, textLength, SQLITE_TRANSIENT);
    rc = sqlite3_step(stmt);
    const char *errmsg = sqlite3_errmsg(db);
    rc = sqlite3_reset(stmt);

    rc = sqlite3_bind_text(stmt, bindIndex, text, textLength, SQLITE_TRANSIENT);
    rc = sqlite3_step(stmt);
    errmsg = sqlite3_errmsg(db);
    rc = sqlite3_reset(stmt);

    errmsg = sqlite3_errmsg(db);
    rc = sqlite3_bind_text(stmt, bindIndex, text, textLength, SQLITE_TRANSIENT);
    rc = sqlite3_step(stmt);
    sqlite3_int64 result = sqlite3_column_int64(stmt, 0);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}