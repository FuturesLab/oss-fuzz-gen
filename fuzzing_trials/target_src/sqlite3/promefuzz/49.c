// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close_v2 at sqlite3.c:172362:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_get_autocommit at sqlite3.c:174945:16 in sqlite3.h
// sqlite3_extended_errcode at sqlite3.c:173836:16 in sqlite3.h
// sqlite3_errcode at sqlite3.c:173827:16 in sqlite3.h
// sqlite3_total_changes at sqlite3.c:172176:16 in sqlite3.h
// sqlite3_error_offset at sqlite3.c:173770:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
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

static sqlite3* open_database() {
    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return NULL;
    }
    return db;
}

static void close_database(sqlite3 *db) {
    if (db) {
        sqlite3_close_v2(db);
    }
}

int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db = open_database();
    if (!db) return 0;

    // Prepare a dummy SQL statement to potentially set some error state
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    sqlite3_exec(db, sql, 0, 0, 0);

    // Fuzz sqlite3_get_autocommit
    int autocommit = sqlite3_get_autocommit(db);

    // Fuzz sqlite3_extended_errcode
    int ext_errcode = sqlite3_extended_errcode(db);

    // Fuzz sqlite3_errcode
    int errcode = sqlite3_errcode(db);

    // Fuzz sqlite3_total_changes
    int total_changes = sqlite3_total_changes(db);

    // Fuzz sqlite3_error_offset
    int error_offset = sqlite3_error_offset(db);

    // Use the input data to perform an operation that might change the state
    char *errMsg = 0;
    size_t sqlSize = Size < 1024 ? Size : 1024; // Limit size for safety
    char *fuzzSql = (char *)malloc(sqlSize + 1);
    if (fuzzSql) {
        memcpy(fuzzSql, Data, sqlSize);
        fuzzSql[sqlSize] = 0; // Null-terminate
        sqlite3_exec(db, fuzzSql, 0, 0, &errMsg);
        free(fuzzSql);
    }

    // Clean up
    if (errMsg) {
        sqlite3_free(errMsg);
    }
    close_database(db);
    return 0;
}