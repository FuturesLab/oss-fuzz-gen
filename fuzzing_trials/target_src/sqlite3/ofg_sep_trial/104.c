#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    // Initialize SQLite
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table
    const char *create_table_sql = "CREATE TABLE test (id INTEGER, value TEXT);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Insert some data into the table for testing
    const char *insert_sql = "INSERT INTO test (id, value) VALUES (1, 'Hello'), (2, 'World');";
    rc = sqlite3_exec(db, insert_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a SELECT statement
    const char *select_sql = "SELECT value FROM test WHERE id = ?;";
    rc = sqlite3_prepare_v2(db, select_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Use the input data to bind to the prepared statement
    if (size >= sizeof(int)) {
        int id = *((int *)data);
        sqlite3_bind_int(stmt, 1, id);

        // Execute the statement
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            // Call the function-under-test
            const void *text = sqlite3_column_text16(stmt, 0);
            // Use the result in some way to avoid compiler optimizations removing the call
            if (text) {
                volatile const void *volatile_text = text;
                (void)volatile_text;
            }
        }
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}