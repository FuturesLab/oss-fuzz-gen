#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_136(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_backup *backup;
    int result;

    // Open a temporary in-memory SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a new table to ensure the database is not empty
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    sqlite3_exec(db, createTableSQL, 0, 0, 0);

    // Create a backup of the database
    backup = sqlite3_backup_init(db, "main", db, "main");
    if (backup == NULL) {
        sqlite3_close(db);
        return 0; // Backup initialization failed
    }

    // Use the input data size to determine how many steps to take
    int steps = (size % 100) + 1; // Ensure at least 1 step
    result = sqlite3_backup_step(backup, steps);

    // Cleanup
    sqlite3_backup_finish(backup);
    sqlite3_close(db);

    return 0; // Return 0 to indicate successful execution
}