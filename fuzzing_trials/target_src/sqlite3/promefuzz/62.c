// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_wal_autocheckpoint at sqlite3.c:173506:16 in sqlite3.h
// sqlite3_db_readonly at sqlite3.c:175999:16 in sqlite3.h
// sqlite3_wal_checkpoint_v2 at sqlite3.c:173557:16 in sqlite3.h
// sqlite3_wal_checkpoint at sqlite3.c:173627:16 in sqlite3.h
// sqlite3_wal_hook at sqlite3.c:173527:18 in sqlite3.h
// sqlite3_txn_state at sqlite3.c:172326:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static int dummy_wal_hook(void *pArg, sqlite3 *db, const char *zDbName, int nFrame) {
    return SQLITE_OK;
}

int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size) {
    sqlite3 *db;
    int rc;
    char *errMsg = 0;
    int checkpoint_mode;
    int log = 0, ckpt = 0;

    // Open a database connection
    rc = sqlite3_open("./dummy_file", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a dummy SQL statement to initialize the database connection
    sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS dummy (id INTEGER PRIMARY KEY, value TEXT);", NULL, NULL, &errMsg);
    if (errMsg) {
        sqlite3_free(errMsg);
    }

    // Fuzzing sqlite3_wal_autocheckpoint
    int N = (Size > 0) ? Data[0] : 0;
    sqlite3_wal_autocheckpoint(db, N);

    // Fuzzing sqlite3_db_readonly
    const char *zDbName = (Size > 1) ? (const char *)&Data[1] : "main";
    sqlite3_db_readonly(db, zDbName);

    // Fuzzing sqlite3_wal_checkpoint_v2
    checkpoint_mode = (Size > 2) ? Data[2] % 5 : SQLITE_CHECKPOINT_PASSIVE;
    sqlite3_wal_checkpoint_v2(db, zDbName, checkpoint_mode, &log, &ckpt);

    // Fuzzing sqlite3_wal_checkpoint
    sqlite3_wal_checkpoint(db, zDbName);

    // Fuzzing sqlite3_wal_hook
    sqlite3_wal_hook(db, dummy_wal_hook, NULL);

    // Fuzzing sqlite3_txn_state
    sqlite3_txn_state(db, zDbName);

    // Close the database connection
    sqlite3_close(db);

    return 0;
}