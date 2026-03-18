#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size) {
    sqlite3 *src_db = NULL;
    sqlite3 *dest_db = NULL;
    sqlite3_backup *backup = NULL;
    int rc;

    // Open source and destination databases in memory
    rc = sqlite3_open(":memory:", &src_db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    rc = sqlite3_open(":memory:", &dest_db);
    if (rc != SQLITE_OK) {
        sqlite3_close(src_db);
        return 0;
    }

    // Create a backup object
    backup = sqlite3_backup_init(dest_db, "main", src_db, "main");
    if (backup == NULL) {
        sqlite3_close(src_db);
        sqlite3_close(dest_db);
        return 0;
    }

    // Call the function-under-test
    int remaining_pages = sqlite3_backup_remaining(backup);

    // Perform a step to progress the backup
    sqlite3_backup_step(backup, 1);

    // Clean up
    sqlite3_backup_finish(backup);
    sqlite3_close(src_db);
    sqlite3_close(dest_db);

    return 0;
}