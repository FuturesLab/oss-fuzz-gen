#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_252(const uint8_t *data, size_t size) {
    sqlite3 *srcDb = NULL;
    sqlite3 *destDb = NULL;
    sqlite3_backup *pBackup = NULL;
    int rc;

    // Initialize SQLite databases
    rc = sqlite3_open(":memory:", &srcDb);
    if (rc != SQLITE_OK || srcDb == NULL) {
        return 0;
    }

    rc = sqlite3_open(":memory:", &destDb);
    if (rc != SQLITE_OK || destDb == NULL) {
        sqlite3_close(srcDb);
        return 0;
    }

    // Execute some SQL on the source database to ensure it has content
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);"
                      "INSERT INTO test (value) VALUES ('test');";
    rc = sqlite3_exec(srcDb, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(srcDb);
        sqlite3_close(destDb);
        return 0;
    }

    // Create a backup object
    pBackup = sqlite3_backup_init(destDb, "main", srcDb, "main");
    if (pBackup == NULL) {
        sqlite3_close(srcDb);
        sqlite3_close(destDb);
        return 0;
    }

    // Perform the backup step
    do {
        rc = sqlite3_backup_step(pBackup, -1);
    } while (rc == SQLITE_OK || rc == SQLITE_BUSY || rc == SQLITE_LOCKED);

    // Fuzz the sqlite3_backup_finish function
    rc = sqlite3_backup_finish(pBackup);

    // Clean up
    sqlite3_close(srcDb);
    sqlite3_close(destDb);

    return 0;
}