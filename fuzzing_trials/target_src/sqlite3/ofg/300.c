#include <stddef.h>  // For size_t
#include <stdlib.h>  // For NULL
#include <stdint.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_300(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt = NULL;
    int index = 1; // Typically, index starts from 1 in SQLite

    // Open an in-memory SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Create a table
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    if (sqlite3_exec(db, createTableSQL, 0, 0, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare an SQL statement for inserting data
    const char *insertSQL = "INSERT INTO test (value) VALUES (?);";
    if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data as a blob
    if (sqlite3_bind_blob(stmt, index, data, size, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement and check the result
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Optionally, you can query the table to further exercise the database
    const char *selectSQL = "SELECT * FROM test;";
    if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, NULL) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            // Access the results if needed
            const unsigned char *text = sqlite3_column_text(stmt, 1);
            (void)text; // Use the text if needed
        }
        sqlite3_finalize(stmt);
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}