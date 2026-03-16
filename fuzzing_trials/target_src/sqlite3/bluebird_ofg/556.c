#include <stdint.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_556(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER, value TEXT);"
                      "INSERT INTO test (id, value) VALUES (1, 'test');"
                      "SELECT value FROM test WHERE id = 1;";
    
    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Execute the SQL statement
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare the SELECT statement
    rc = sqlite3_prepare_v2(db, "SELECT value FROM test WHERE id = 1", -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Step through the results
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Call the function-under-test
        const unsigned char *text = sqlite3_column_text(stmt, 0);
        if (text) {
            // Use the text in some way, here we just check its length
            size_t text_len = strlen((const char *)text);
        }
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}