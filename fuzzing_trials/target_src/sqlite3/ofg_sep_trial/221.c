#include <stddef.h>  // Include for size_t and NULL
#include <stdint.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_221(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;  // No need to proceed if there's no data
    }

    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a table
    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS fuzz_table (id INTEGER PRIMARY KEY, data BLOB);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare an SQL statement to insert the data
    const char *insert_sql = "INSERT INTO fuzz_table (data) VALUES (?1);";
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data as a blob
    rc = sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Clean up
    sqlite3_finalize(stmt);

    // Prepare a query to select the data back
    const char *select_sql = "SELECT data FROM fuzz_table WHERE id = 1;";
    rc = sqlite3_prepare_v2(db, select_sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the select statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Optionally, do something with the retrieved data
        const void *retrieved_data = sqlite3_column_blob(stmt, 0);
        int retrieved_size = sqlite3_column_bytes(stmt, 0);
        // For fuzzing purposes, we don't need to do anything specific with retrieved_data
    }

    // Final clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}