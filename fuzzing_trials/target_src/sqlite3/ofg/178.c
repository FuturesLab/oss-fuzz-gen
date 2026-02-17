#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_178(const uint8_t *data, size_t size) {
    sqlite3 *sourceDb = NULL;
    sqlite3 *destDb = NULL;
    sqlite3_backup *backup = NULL;

    // Initialize SQLite databases
    if (sqlite3_open(":memory:", &sourceDb) != SQLITE_OK) {
        return 0; // Failed to open source database
    }
    if (sqlite3_open(":memory:", &destDb) != SQLITE_OK) {
        sqlite3_close(sourceDb);
        return 0; // Failed to open destination database
    }

    // Create a table in the source database
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    sqlite3_exec(sourceDb, createTableSQL, 0, 0, 0);

    // Insert some data into the source database
    const char *insertSQL = "INSERT INTO test (value) VALUES ('test_value');";
    sqlite3_exec(sourceDb, insertSQL, 0, 0, 0);

    // Prepare the backup operation
    backup = sqlite3_backup_init(destDb, "main", sourceDb, "main");
    if (backup) {
        // Perform the backup
        sqlite3_backup_step(backup, -1); // -1 means copy all pages
        sqlite3_backup_finish(backup);
    }

    // Clean up
    sqlite3_close(sourceDb);
    sqlite3_close(destDb);

    return 0;
}