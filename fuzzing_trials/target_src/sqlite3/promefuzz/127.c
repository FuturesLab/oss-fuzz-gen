// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_column_count at sqlite3.c:79599:16 in sqlite3.h
// sqlite3_column_type at sqlite3.c:79770:16 in sqlite3.h
// sqlite3_column_int at sqlite3.c:79739:16 in sqlite3.h
// sqlite3_column_value at sqlite3.c:79754:27 in sqlite3.h
// sqlite3_value_int at sqlite3.c:78537:16 in sqlite3.h
// sqlite3_bind_value at sqlite3.c:80193:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
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
#include <stdlib.h>
#include <string.h>

static void prepareDatabase(sqlite3 **db, sqlite3_stmt **stmt) {
    int rc = sqlite3_open(":memory:", db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db));
        return;
    }

    char *errMsg = NULL;
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);"
                      "INSERT INTO test (value) VALUES ('sample');"
                      "SELECT * FROM test;";
    rc = sqlite3_exec(*db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    const char *selectSQL = "SELECT * FROM test;";
    rc = sqlite3_prepare_v2(*db, selectSQL, -1, stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(*db));
    }
}

int LLVMFuzzerTestOneInput_127(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    prepareDatabase(&db, &stmt);

    if (stmt) {
        // Fuzzing sqlite3_column_count
        int colCount = sqlite3_column_count(stmt);

        for (int i = 0; i < colCount; i++) {
            // Fuzzing sqlite3_column_type
            int colType = sqlite3_column_type(stmt, i);

            // Fuzzing sqlite3_column_int
            int colInt = sqlite3_column_int(stmt, i);

            // Fuzzing sqlite3_column_value
            sqlite3_value *colValue = sqlite3_column_value(stmt, i);
            if (colValue) {
                // Fuzzing sqlite3_value_int
                int valueInt = sqlite3_value_int(colValue);

                // Fuzzing sqlite3_bind_value
                sqlite3_bind_value(stmt, i + 1, colValue);
            }
        }

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    if (db) {
        sqlite3_close(db);
    }

    return 0;
}