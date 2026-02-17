#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    // Ensure the input data is not null and has a valid size
    if (data == NULL || size == 0) {
        return 0; // Invalid input, do nothing
    }

    sqlite3 *db;
    int rc;

    // Open a new in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    char *err_msg = NULL;
    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Prepare an insert statement
    const char *insert_sql = "INSERT INTO test (value) VALUES (?);";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Bind data to the statement
    rc = sqlite3_bind_text(stmt, 1, (const char *)data, size, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Failed to bind data
    }

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Failed to execute statement
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Call the function under test: query the inserted value
    const char *select_sql = "SELECT value FROM test WHERE id = 1;";
    sqlite3_stmt *select_stmt;
    rc = sqlite3_prepare_v2(db, select_sql, -1, &select_stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare select statement
    }

    // Step through the results
    rc = sqlite3_step(select_stmt);
    if (rc == SQLITE_ROW) {
        const char *value = (const char *)sqlite3_column_text(select_stmt, 0);
        // Here we can do something with the retrieved value if needed
        // For example, we can check if the retrieved value matches the input
        if (value != NULL && size > 0) {
            // This ensures that we are actually using the data
            // We can also log or process the value if needed
        }
    }

    // Finalize the select statement
    sqlite3_finalize(select_stmt);

    // Get the number of changes made
    int changes = sqlite3_changes(db);

    // Clean up and close the database
    sqlite3_close(db);

    return changes; // Return the number of changes made
}