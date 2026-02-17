#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_177(const uint8_t *data, size_t size) {
    sqlite3 *sourceDb;
    sqlite3 *destDb;
    sqlite3_backup *backup;
    const char *sourceName = "source_db";
    const char *destName = "dest_db";

    // Initialize SQLite databases
    sqlite3_open(":memory:", &sourceDb);
    sqlite3_open(":memory:", &destDb);

    // Create a table in the source database to ensure it has some data
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    sqlite3_exec(sourceDb, createTableSQL, 0, 0, 0);

    // Insert data into the source database
    const char *insertSQL = "INSERT INTO test (value) VALUES ('test_value');";
    sqlite3_exec(sourceDb, insertSQL, 0, 0, 0);

    // Initialize backup
    backup = sqlite3_backup_init(destDb, destName, sourceDb, sourceName);
    if (backup) {
        // Perform the backup
        sqlite3_backup_step(backup, -1); // -1 means copy all pages
        sqlite3_backup_finish(backup);
    }

    // Cleanup
    sqlite3_close(sourceDb);
    sqlite3_close(destDb);

    return 0;
}