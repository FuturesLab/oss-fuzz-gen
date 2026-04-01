// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_config at sqlite3.c:171444:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_db_status at sqlite3.c:11036:16 in sqlite3.h
// sqlite3_db_status at sqlite3.c:11036:16 in sqlite3.h
// sqlite3_db_status at sqlite3.c:11036:16 in sqlite3.h
// sqlite3_db_status at sqlite3.c:11036:16 in sqlite3.h
// sqlite3_db_status at sqlite3.c:11036:16 in sqlite3.h
// sqlite3_db_status at sqlite3.c:11036:16 in sqlite3.h
// sqlite3_db_status at sqlite3.c:11036:16 in sqlite3.h
// sqlite3_db_status at sqlite3.c:11036:16 in sqlite3.h
// sqlite3_db_status at sqlite3.c:11036:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_status at sqlite3.c:10769:16 in sqlite3.h
// sqlite3_status at sqlite3.c:10769:16 in sqlite3.h
// sqlite3_status at sqlite3.c:10769:16 in sqlite3.h
// sqlite3_status at sqlite3.c:10769:16 in sqlite3.h
// sqlite3_status at sqlite3.c:10769:16 in sqlite3.h
// sqlite3_mprintf at sqlite3.c:19329:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_mprintf at sqlite3.c:19329:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <stdint.h>
#include <string.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    char *errMsg = 0;
    int rc;
    int cur, hiwtr;
    char *sql = "CREATE TABLE IF NOT EXISTS fuzz_table (id INTEGER PRIMARY KEY, data TEXT);";
    char *mprintfResult;

    rc = sqlite3_config(SQLITE_CONFIG_SINGLETHREAD);
    if (rc != SQLITE_OK) {
        return 0;
    }

    rc = sqlite3_open("./dummy_file", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    sqlite3_errmsg(db);

    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
    }

    rc = sqlite3_db_status(db, SQLITE_DBSTATUS_LOOKASIDE_USED, &cur, &hiwtr, 0);
    rc = sqlite3_db_status(db, SQLITE_DBSTATUS_CACHE_USED, &cur, &hiwtr, 0);
    rc = sqlite3_db_status(db, SQLITE_DBSTATUS_SCHEMA_USED, &cur, &hiwtr, 0);
    rc = sqlite3_db_status(db, SQLITE_DBSTATUS_STMT_USED, &cur, &hiwtr, 0);
    rc = sqlite3_db_status(db, SQLITE_DBSTATUS_LOOKASIDE_HIT, &cur, &hiwtr, 0);
    rc = sqlite3_db_status(db, SQLITE_DBSTATUS_LOOKASIDE_MISS_SIZE, &cur, &hiwtr, 0);
    rc = sqlite3_db_status(db, SQLITE_DBSTATUS_LOOKASIDE_MISS_FULL, &cur, &hiwtr, 0);
    rc = sqlite3_db_status(db, SQLITE_DBSTATUS_CACHE_HIT, &cur, &hiwtr, 0);
    rc = sqlite3_db_status(db, SQLITE_DBSTATUS_CACHE_MISS, &cur, &hiwtr, 0);

    rc = sqlite3_close(db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    rc = sqlite3_status(SQLITE_STATUS_MEMORY_USED, &cur, &hiwtr, 0);
    rc = sqlite3_status(SQLITE_STATUS_MALLOC_SIZE, &cur, &hiwtr, 0);
    rc = sqlite3_status(SQLITE_STATUS_MALLOC_COUNT, &cur, &hiwtr, 0);
    rc = sqlite3_status(SQLITE_STATUS_PAGECACHE_USED, &cur, &hiwtr, 0);
    rc = sqlite3_status(SQLITE_STATUS_PAGECACHE_OVERFLOW, &cur, &hiwtr, 0);

    mprintfResult = sqlite3_mprintf("Data: %.*s", (int)Size, Data);
    sqlite3_free(mprintfResult);

    mprintfResult = sqlite3_mprintf("Size: %zu", Size);
    sqlite3_free(mprintfResult);

    rc = sqlite3_open("./dummy_file", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    sqlite3_errmsg(db);

    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
    }

    rc = sqlite3_exec(db, "INSERT INTO fuzz_table (data) VALUES ('fuzzing');", callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
    }

    rc = sqlite3_exec(db, "SELECT * FROM fuzz_table;", callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
    }

    sqlite3_free(errMsg);

    rc = sqlite3_close(db);
    return 0;
}