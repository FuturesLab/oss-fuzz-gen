#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_187(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    int column_index = 0;

    // Initialize SQLite database in memory
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

    // Insert some data into the table
    const char *insert_sql = "INSERT INTO test (id, value) VALUES (1, 'test');";
    rc = sqlite3_exec(db, insert_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement from the input data
    char *query = (char *)malloc(size + 1);
    if (query == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(query, data, size);
    query[size] = '\0';

    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    free(query);

    if (rc == SQLITE_OK) {
        // Execute the statement
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            // Call the function-under-test
            int bytes = sqlite3_column_bytes(stmt, column_index);
        }
        sqlite3_finalize(stmt);
    }

    // Close the database connection
    sqlite3_close(db);
    return 0;
}