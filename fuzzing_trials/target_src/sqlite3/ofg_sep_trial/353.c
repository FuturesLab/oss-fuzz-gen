#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

extern int LLVMFuzzerTestOneInput_353(const uint8_t *data, size_t size) {
    // Initialize SQLite3
    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Create a test table
    sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);", 0, 0, 0);

    // Create a backup object
    sqlite3_backup *backup = sqlite3_backup_init(db, "main", db, "main");

    if (backup != NULL) {
        // Call the function-under-test
        int pagecount = sqlite3_backup_pagecount(backup);

        // Use the pagecount to prevent compiler optimizations
        if (pagecount < 0) {
            sqlite3_backup_finish(backup);
            sqlite3_close(db);
            return 0;
        }

        // Finish the backup
        sqlite3_backup_finish(backup);
    }

    // Close the database connection
    sqlite3_close(db);

    return 0;
}