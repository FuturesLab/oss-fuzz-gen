#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

// Initialize a SQLite database in memory
static sqlite3* initialize_database() {
    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db);
    if (rc) {
        sqlite3_close(db);
        return NULL;
    }
    return db;
}

int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    // Initialize database
    sqlite3 *db = initialize_database();
    if (db == NULL) {
        return 0; // Failed to initialize database
    }

    // Prepare the SQL statement
    const char *sql = (const char *)data;
    int sql_length = (int)size;
    sqlite3_stmt *stmt = NULL;
    const char *tail = NULL;

    // Call the function-under-test
    int rc = sqlite3_prepare(db, sql, sql_length, &stmt, &tail);

    // Finalize the statement if it was successfully prepared
    if (rc == SQLITE_OK && stmt != NULL) {
        sqlite3_finalize(stmt);
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}