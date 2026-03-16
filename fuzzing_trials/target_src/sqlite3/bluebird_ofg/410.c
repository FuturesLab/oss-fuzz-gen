#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_410(const uint8_t *data, size_t size) {
    // Ensure there is data to process
    if (size == 0) {
        return 0;
    }

    // Open an in-memory SQLite database
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Use the provided data as the SQL input
    const char *sql = (const char *)data;

    // Prepare the SQL statement
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, (int)size, &stmt, NULL);

    // Finalize the statement if it was prepared
    if (rc == SQLITE_OK) {
        sqlite3_finalize(stmt);
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}