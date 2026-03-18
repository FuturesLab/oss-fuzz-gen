// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_reset at sqlite3.c:78461:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_stmt_busy at sqlite3.c:80407:16 in sqlite3.h
// sqlite3_stmt_status at sqlite3.c:80439:16 in sqlite3.h
// sqlite3_transfer_bindings at sqlite3.c:80324:16 in sqlite3.h
// sqlite3_expired at sqlite3.c:78362:16 in sqlite3.h
// sqlite3_stmt_explain at sqlite3.c:80371:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
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
#include <string.h>

static void prepare_dummy_db(sqlite3 **db) {
    if (sqlite3_open(":memory:", db) != SQLITE_OK) {
        *db = NULL;
    }
}

static void prepare_stmt(sqlite3 *db, const char *sql, sqlite3_stmt **stmt) {
    if (db && sql && sqlite3_prepare_v2(db, sql, -1, stmt, NULL) != SQLITE_OK) {
        *stmt = NULL;
    }
}

int LLVMFuzzerTestOneInput_98(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt1 = NULL, *stmt2 = NULL;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value TEXT);";

    prepare_dummy_db(&db);
    if (!db) return 0;

    prepare_stmt(db, sql, &stmt1);
    if (!stmt1) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement to create table
    sqlite3_step(stmt1);
    sqlite3_reset(stmt1);

    // Prepare a statement to insert data
    sql = "INSERT INTO test (value) VALUES (?);";
    prepare_stmt(db, sql, &stmt2);
    if (!stmt2) {
        sqlite3_finalize(stmt1);
        sqlite3_close(db);
        return 0;
    }

    // Bind input data to the statement
    if (Size > 0) {
        sqlite3_bind_text(stmt2, 1, (const char *)Data, Size, SQLITE_TRANSIENT);
    }

    // Execute the statement
    sqlite3_step(stmt2);

    // Fuzzing target functions
    sqlite3_stmt_busy(stmt1);
    sqlite3_stmt_status(stmt1, SQLITE_STMTSTATUS_FULLSCAN_STEP, 0);
    sqlite3_transfer_bindings(stmt1, stmt2);
    sqlite3_expired(stmt1);
    sqlite3_stmt_explain(stmt1, 0);

    // Cleanup
    sqlite3_finalize(stmt1);
    sqlite3_finalize(stmt2);
    sqlite3_close(db);

    return 0;
}