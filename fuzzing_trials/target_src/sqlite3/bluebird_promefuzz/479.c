#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include <stdlib.h>
#include "stdio.h"
#include "sqlite3.h"
#include "stdint.h"
#include "stddef.h"
#include "stdio.h"
#include <stdlib.h>
#include "string.h"

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

int LLVMFuzzerTestOneInput_479(const uint8_t *Data, size_t Size) {
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