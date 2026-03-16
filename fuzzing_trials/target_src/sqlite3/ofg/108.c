#include <stddef.h>  // For size_t
#include <stdlib.h>  // For NULL
#include <stdint.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    sqlite3 *source_db = NULL;
    sqlite3 *dest_db = NULL;
    sqlite3_backup *backup = NULL;
    int pages = 1; // Number of pages to copy in each step
    int rc;

    // Open source and destination databases in memory
    rc = sqlite3_open(":memory:", &source_db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    rc = sqlite3_open(":memory:", &dest_db);
    if (rc != SQLITE_OK) {
        sqlite3_close(source_db);
        return 0;
    }

    // Create a backup object
    backup = sqlite3_backup_init(dest_db, "main", source_db, "main");
    if (backup == NULL) {
        sqlite3_close(source_db);
        sqlite3_close(dest_db);
        return 0;
    }

    // Use the data and size as input for the pages parameter
    if (size > 0) {
        pages = data[0] % 10 + 1; // Ensure pages is between 1 and 10
    }

    // Call the function-under-test
    sqlite3_backup_step(backup, pages);

    // Clean up
    sqlite3_backup_finish(backup);
    sqlite3_close(source_db);
    sqlite3_close(dest_db);

    return 0;
}