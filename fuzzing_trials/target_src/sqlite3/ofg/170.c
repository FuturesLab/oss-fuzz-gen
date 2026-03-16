#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

// Initialize the SQLite database
static sqlite3 *initialize_database() {
    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db); // Open an in-memory database
    if (rc != SQLITE_OK) {
        return NULL;
    }

    // Create a sample table to ensure the database is not empty
    const char *create_table_sql = "CREATE TABLE test(id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return NULL;
    }

    // Insert a sample row
    const char *insert_sql = "INSERT INTO test(value) VALUES('sample');";
    rc = sqlite3_exec(db, insert_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return NULL;
    }

    return db;
}

int LLVMFuzzerTestOneInput_170(const uint8_t *data, size_t size) {
    sqlite3 *db = initialize_database();
    if (db == NULL) {
        return 0;
    }

    // Call the function under test
    sqlite3_int64 changes = sqlite3_total_changes64(db);

    // Use the result to prevent optimization
    if (changes == 0) {
        // Perform some operation if needed
    }

    sqlite3_close(db);
    return 0;
}