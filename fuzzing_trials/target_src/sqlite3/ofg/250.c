#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_250(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER, value TEXT);"
                      "INSERT INTO test (id, value) VALUES (1, 'Hello'), (2, 'World');"
                      "SELECT value FROM test WHERE id = ?;";

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Execute the SQL to create table and insert data
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, "SELECT value FROM test WHERE id = ?;", -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the first parameter to the statement
    int id = (size > 0) ? data[0] % 3 : 0; // Ensure id is 0, 1, or 2
    sqlite3_bind_int(stmt, 1, id);

    // Execute the statement and call the function-under-test
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *text = sqlite3_column_text(stmt, 0);
        // Use the text in some way to prevent optimization out
        if (text) {
            volatile unsigned char dummy = text[0];
            (void)dummy;
        }
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}