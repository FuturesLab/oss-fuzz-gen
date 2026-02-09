#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h> // Include limits.h for INT_MAX
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
    // Initialize the SQLite database and backup objects
    sqlite3 *db = NULL;
    sqlite3_backup *backup = NULL;
    int result;

    // Open a temporary SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a table in the database for backup purposes
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    sqlite3_exec(db, create_table_sql, NULL, NULL, NULL);

    // Begin a backup operation
    backup = sqlite3_backup_init(db, "main", db, "main");
    if (backup == NULL) {
        sqlite3_close(db);
        return 0; // Backup initialization failed
    }

    // Define the number of steps to perform based on the input size
    int steps = (size > INT_MAX) ? INT_MAX : (int)size;

    // Call the function under test
    result = sqlite3_backup_step(backup, steps);

    // Cleanup
    sqlite3_backup_finish(backup);
    sqlite3_close(db);

    return 0;
}