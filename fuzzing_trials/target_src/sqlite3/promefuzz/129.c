// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_total_changes64 at sqlite3.c:172167:26 in sqlite3.h
// sqlite3_last_insert_rowid at sqlite3.c:172123:25 in sqlite3.h
// sqlite3_set_last_insert_rowid at sqlite3.c:172136:17 in sqlite3.h
// sqlite3_update_hook at sqlite3.c:173372:18 in sqlite3.h
// sqlite3_changes64 at sqlite3.c:172151:26 in sqlite3.h
// sqlite3_wal_hook at sqlite3.c:173527:18 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
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

static void test_sqlite3_total_changes64(sqlite3 *db) {
    sqlite3_int64 total_changes = sqlite3_total_changes64(db);
    (void)total_changes; // Suppress unused variable warning
}

static void test_sqlite3_last_insert_rowid(sqlite3 *db) {
    sqlite3_int64 last_rowid = sqlite3_last_insert_rowid(db);
    (void)last_rowid; // Suppress unused variable warning
}

static void test_sqlite3_set_last_insert_rowid(sqlite3 *db) {
    sqlite3_int64 dummy_rowid = 42; // Arbitrary rowid for testing
    sqlite3_set_last_insert_rowid(db, dummy_rowid);
}

static void update_hook(void *pArg, int op, const char *zDb, const char *zTbl, sqlite3_int64 rowid) {
    // Dummy update hook callback
    (void)pArg;
    (void)op;
    (void)zDb;
    (void)zTbl;
    (void)rowid;
}

static void test_sqlite3_update_hook(sqlite3 *db) {
    sqlite3_update_hook(db, update_hook, NULL);
}

static void test_sqlite3_changes64(sqlite3 *db) {
    sqlite3_int64 changes = sqlite3_changes64(db);
    (void)changes; // Suppress unused variable warning
}

static int wal_hook(void *pArg, sqlite3 *db, const char *zDbName, int nPages) {
    // Dummy WAL hook callback
    (void)pArg;
    (void)db;
    (void)zDbName;
    (void)nPages;
    return SQLITE_OK;
}

static void test_sqlite3_wal_hook(sqlite3 *db) {
    sqlite3_wal_hook(db, wal_hook, NULL);
}

int LLVMFuzzerTestOneInput_129(const uint8_t *Data, size_t Size) {
    sqlite3 *db;
    int rc;

    // Initialize SQLite database connection
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Test the target functions with the database connection
    test_sqlite3_total_changes64(db);
    test_sqlite3_last_insert_rowid(db);
    test_sqlite3_set_last_insert_rowid(db);
    test_sqlite3_update_hook(db);
    test_sqlite3_changes64(db);
    test_sqlite3_wal_hook(db);

    // Close the SQLite database connection
    sqlite3_close(db);

    return 0;
}