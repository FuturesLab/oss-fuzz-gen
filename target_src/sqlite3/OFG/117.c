#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_int64 changes;

    // Initialize SQLite database in memory
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table to ensure there are changes
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    sqlite3_exec(db, create_table_sql, 0, 0, 0);

    // Insert a row to ensure there are changes
    const char *insert_sql = "INSERT INTO test (value) VALUES (?);";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
    
    // Bind data to the prepared statement
    sqlite3_bind_text(stmt, 1, (const char *)data, (int)size, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    // Call the function under test
    changes = sqlite3_total_changes64(db);

    // Clean up
    sqlite3_close(db);

    return 0;
}