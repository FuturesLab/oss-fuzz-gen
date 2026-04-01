// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_interrupt at sqlite3.c:172907:17 in sqlite3.h
// sqlite3_changes64 at sqlite3.c:172151:26 in sqlite3.h
// sqlite3_set_authorizer at sqlite3.c:110840:16 in sqlite3.h
// sqlite3_extended_errcode at sqlite3.c:173836:16 in sqlite3.h
// sqlite3_last_insert_rowid at sqlite3.c:172123:25 in sqlite3.h
// sqlite3_rollback_hook at sqlite3.c:173397:18 in sqlite3.h
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

static int authorizerCallback(void *pUserData, int actionCode, const char *param1, const char *param2, const char *dbName, const char *triggerName) {
    // Simple authorizer callback that allows all actions
    return SQLITE_OK;
}

static void rollbackCallback(void *pArg) {
    // Simple rollback hook callback
}

int LLVMFuzzerTestOneInput_113(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare a dummy SQL statement
    const char *sql = "CREATE TABLE dummy (id INTEGER PRIMARY KEY, value TEXT);";
    sqlite3_exec(db, sql, 0, 0, 0);

    // Fuzzing sqlite3_interrupt
    sqlite3_interrupt(db);

    // Fuzzing sqlite3_changes64
    sqlite3_int64 changes = sqlite3_changes64(db);

    // Fuzzing sqlite3_set_authorizer
    sqlite3_set_authorizer(db, authorizerCallback, NULL);

    // Fuzzing sqlite3_extended_errcode
    int errcode = sqlite3_extended_errcode(db);

    // Fuzzing sqlite3_last_insert_rowid
    sqlite3_int64 lastRowId = sqlite3_last_insert_rowid(db);

    // Fuzzing sqlite3_rollback_hook
    sqlite3_rollback_hook(db, rollbackCallback, NULL);

    // Cleanup
    sqlite3_close(db);

    return 0;
}