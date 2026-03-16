// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_column_text at sqlite3.c:79749:33 in sqlite3.h
// sqlite3_snprintf at sqlite3.c:19369:18 in sqlite3.h
// sqlite3_snprintf at sqlite3.c:19369:18 in sqlite3.h
// sqlite3_reset at sqlite3.c:78461:16 in sqlite3.h
// sqlite3_sql at sqlite3.c:80471:24 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

static void prepare_database(sqlite3 **db, sqlite3_stmt **stmt) {
    sqlite3_open(":memory:", db);
    sqlite3_exec(*db, "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);", 0, 0, 0);
    sqlite3_exec(*db, "INSERT INTO test (value) VALUES ('test1'), ('test2');", 0, 0, 0);
    sqlite3_prepare_v2(*db, "SELECT value FROM test WHERE id = ?;", -1, stmt, 0);
}

static void cleanup(sqlite3 *db, sqlite3_stmt *stmt) {
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    prepare_database(&db, &stmt);

    if (Size > 0) {
        int index = Data[0] % 2 + 1; // Choose between 1 or 2
        sqlite3_bind_text(stmt, 1, (const char *)&index, -1, SQLITE_TRANSIENT);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char *text = sqlite3_column_text(stmt, 0);
            if (text) {
                char buffer[100];
                sqlite3_snprintf(sizeof(buffer), buffer, "Value: %s", text);
                sqlite3_snprintf(sizeof(buffer), buffer, "Value: %s", text);
            }
        }

        sqlite3_reset(stmt);
        const char *sql = sqlite3_sql(stmt);
        if (sql) {
            printf("SQL: %s\n", sql);
        }
    }

    cleanup(db, stmt);

    return 0;
}