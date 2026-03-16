// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_bind_blob at sqlite3.c:80082:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_column_bytes at sqlite3.c:79724:16 in sqlite3.h
// sqlite3_column_blob at sqlite3.c:79714:24 in sqlite3.h
// sqlite3_column_bytes at sqlite3.c:79724:16 in sqlite3.h
// sqlite3_column_blob at sqlite3.c:79714:24 in sqlite3.h
// sqlite3_stmt_isexplain at sqlite3.c:80364:16 in sqlite3.h
// sqlite3_reset at sqlite3.c:78461:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

static void initializeDatabase(sqlite3 **db, sqlite3_stmt **stmt, const uint8_t *Data, size_t Size) {
    int rc;
    char *errMsg = 0;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, data BLOB);"
                      "INSERT INTO test (data) VALUES (?);";

    rc = sqlite3_open(":memory:", db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
        return;
    }

    rc = sqlite3_exec(*db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    rc = sqlite3_prepare_v2(*db, "SELECT data FROM test WHERE id = 1;", -1, stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(*db));
    }

    rc = sqlite3_bind_blob(*stmt, 1, Data, (int)Size, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to bind blob: %s\n", sqlite3_errmsg(*db));
    }
}

int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc;

    initializeDatabase(&db, &stmt, Data, Size);

    if (stmt) {
        int colIndex = 0;
        sqlite3_column_bytes(stmt, colIndex);
        sqlite3_column_blob(stmt, colIndex);
        sqlite3_column_bytes(stmt, colIndex);
        sqlite3_column_blob(stmt, colIndex);

        sqlite3_stmt_isexplain(stmt);
        sqlite3_reset(stmt);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
            fprintf(stderr, "Failed to step: %s\n", sqlite3_errmsg(db));
        }

        sqlite3_errmsg(db);
        sqlite3_errmsg(db);

        sqlite3_finalize(stmt);
    }

    if (db) {
        sqlite3_close(db);
    }

    return 0;
}