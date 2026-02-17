#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_159(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int result;

    // Initialize SQLite
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Prepare a statement with a valid SQL command
    const char *sql = "SELECT 1;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Call the function under test
    result = sqlite3_stmt_isexplain(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0; // Return success
}