#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    sqlite3 *srcDb = NULL;
    sqlite3 *destDb = NULL;
    sqlite3_backup *backup = NULL;
    int pageCount = 1; // Default page count for the backup step

    // Open source and destination databases in memory
    if (sqlite3_open(":memory:", &srcDb) != SQLITE_OK) {
        return 0;
    }
    if (sqlite3_open(":memory:", &destDb) != SQLITE_OK) {
        sqlite3_close(srcDb);
        return 0;
    }

    // Create a backup object
    backup = sqlite3_backup_init(destDb, "main", srcDb, "main");
    if (backup == NULL) {
        sqlite3_close(srcDb);
        sqlite3_close(destDb);
        return 0;
    }

    // Use the first byte of data to determine the page count, if available
    if (size > 0) {
        pageCount = (int)data[0];
    }

    // Call the function-under-test
    sqlite3_backup_step(backup, pageCount);

    // Clean up
    sqlite3_backup_finish(backup);
    sqlite3_close(srcDb);
    sqlite3_close(destDb);

    return 0;
}