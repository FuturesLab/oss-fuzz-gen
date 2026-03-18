#include <stdint.h>
#include <stddef.h> // Include for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_107(const uint8_t *data, size_t size) {
    sqlite3 *src_db = NULL;
    sqlite3 *dest_db = NULL;
    sqlite3_backup *backup = NULL;
    int pages = -1; // Use -1 to copy all pages
    int rc;
    char *errMsg = NULL;

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

    // Create a table and insert some data into the source database
    rc = sqlite3_exec(src_db, "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);", NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(src_db);
        sqlite3_close(dest_db);
        return 0;
    }

    // Insert data into the table
    rc = sqlite3_exec(src_db, "INSERT INTO test (value) VALUES ('Hello, World!');", NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(src_db);
        sqlite3_close(dest_db);
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
    sqlite3_backup_step(backup, pages);

    // Cleanup
    sqlite3_backup_finish(backup);
    sqlite3_close(src_db);
    sqlite3_close(dest_db);

    return 0;
}