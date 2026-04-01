// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_wal_checkpoint at sqlite3.c:173627:16 in sqlite3.h
// sqlite3_db_readonly at sqlite3.c:175999:16 in sqlite3.h
// sqlite3_wal_autocheckpoint at sqlite3.c:173506:16 in sqlite3.h
// sqlite3_wal_hook at sqlite3.c:173527:18 in sqlite3.h
// sqlite3_txn_state at sqlite3.c:172326:16 in sqlite3.h
// sqlite3_wal_checkpoint_v2 at sqlite3.c:173557:16 in sqlite3.h
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

static int dummy_wal_callback(void *pArg, sqlite3 *db, const char *zDb, int nFrame) {
    return SQLITE_OK;
}

int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    int rc = sqlite3_open("./dummy_file", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    char *zDbName = "main";
    int checkpointMode = SQLITE_CHECKPOINT_PASSIVE;
    int nLogFrames = 0;
    int nCkptFrames = 0;
    
    // Fuzz sqlite3_wal_checkpoint
    sqlite3_wal_checkpoint(db, zDbName);

    // Fuzz sqlite3_db_readonly
    sqlite3_db_readonly(db, zDbName);

    // Fuzz sqlite3_wal_autocheckpoint
    sqlite3_wal_autocheckpoint(db, (int)Data[0]);

    // Fuzz sqlite3_wal_hook
    sqlite3_wal_hook(db, dummy_wal_callback, NULL);

    // Fuzz sqlite3_txn_state
    sqlite3_txn_state(db, zDbName);

    // Fuzz sqlite3_wal_checkpoint_v2
    sqlite3_wal_checkpoint_v2(db, zDbName, checkpointMode, &nLogFrames, &nCkptFrames);

    sqlite3_close(db);
    return 0;
}