#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_353(const uint8_t *data, size_t size) {
    // Initialize SQLite library
    sqlite3_initialize();

    // Create an in-memory database
    sqlite3 *sourceDb;
    sqlite3_open(":memory:", &sourceDb);

    // Create another in-memory database
    sqlite3 *destDb;
    sqlite3_open(":memory:", &destDb);

    // If there is any data, use it to create a table and insert a row
    if (size > 0) {
        char *errMsg = 0;
        // Create a table
        sqlite3_exec(sourceDb, "CREATE TABLE test (id INTEGER PRIMARY KEY, value BLOB);", 0, 0, &errMsg);

        // Insert the data into the table
        sqlite3_stmt *stmt;
        sqlite3_prepare_v2(sourceDb, "INSERT INTO test (value) VALUES (?);", -1, &stmt, 0);
        sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    // Create a backup object
    sqlite3_backup *backup = sqlite3_backup_init(destDb, "main", sourceDb, "main");

    if (backup != NULL) {
        // Call the function-under-test
        int pageCount = sqlite3_backup_pagecount(backup);

        // Perform some operation with the result to avoid unused variable warning
        if (pageCount < 0) {
            // Handle error if needed
        }

        // Finish the backup
        sqlite3_backup_finish(backup);
    }

    // Close the databases
    sqlite3_close(destDb);
    sqlite3_close(sourceDb);

    // Shutdown SQLite library
    sqlite3_shutdown();

    return 0;
}