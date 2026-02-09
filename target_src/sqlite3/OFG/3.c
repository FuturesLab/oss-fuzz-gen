#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h> // Include for size_t and memcpy

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_int64 last_inserted_id;

    // Initialize the SQLite database connection
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a table to insert data into
    const char *create_table_sql = "CREATE TABLE test_table (id INTEGER PRIMARY KEY AUTOINCREMENT, value TEXT);";
    char *err_msg = NULL;
    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Prepare an insert statement
    const char *insert_sql = "INSERT INTO test_table (value) VALUES (?);";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Bind the input data to the prepared statement
    rc = sqlite3_bind_text(stmt, 1, (const char *)data, size, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Failed to bind data
    }

    // Execute the insert statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Failed to execute statement
    }

    // Call the function under test
    last_inserted_id = sqlite3_last_insert_rowid(db);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    // Optionally, you could use last_inserted_id for further testing or assertions
    return 0;
}