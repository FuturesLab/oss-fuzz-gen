#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_203(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    sqlite3 *db;
    sqlite3_stmt *stmt1;
    sqlite3_stmt *stmt2;
    int rc;

    // Open a temporary SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Prepare two statements
    const char *insert_sql = "INSERT INTO test (value) VALUES (?);";
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt1, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare first statement
    }

    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt2, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt1);
        sqlite3_close(db);
        return 0; // Failed to prepare second statement
    }

    // Bind the input data to the first statement
    sqlite3_bind_text(stmt1, 1, (const char *)data, (int)size, SQLITE_STATIC);

    // Call the function under test
    sqlite3_transfer_bindings(stmt1, stmt2);

    // Finalize statements
    sqlite3_finalize(stmt1);
    sqlite3_finalize(stmt2);
    
    // Close the database
    sqlite3_close(db);

    return 0;
}