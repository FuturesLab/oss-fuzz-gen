#include <sqlite3.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h> // Include for size_t

int LLVMFuzzerTestOneInput_362(const uint8_t *data, size_t size) {
    sqlite3_stmt *stmt;
    int rc;

    // Create a new SQLite database in memory
    sqlite3 *db;
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Prepare a simple SQL statement
    const char *sql = "CREATE TABLE test (column_name TEXT); INSERT INTO test (column_name) VALUES (?);";
    rc = sqlite3_exec(db, sql, 0, 0, 0); // Create table and insert one row
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    rc = sqlite3_prepare_v2(db, "SELECT * FROM test WHERE column_name = ?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Ensure size is within a reasonable limit for binding
    if (size > 100) {
        size = 100; // Limit the size to avoid excessive memory usage
    }

    // Bind the input data as UTF-16 text
    // SQLite expects the text to be in UTF-16 format, so we need to convert it
    // Here we assume that the input data is UTF-8 and convert it to UTF-16
    int utf16_size = size * 2; // Each UTF-8 character can be up to 4 bytes, but we will use 2 bytes for UTF-16
    void *utf16_data = malloc(utf16_size + 2); // +2 for null terminator
    if (utf16_data == NULL) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Memory allocation failed
    }

    // Convert input data to UTF-16
    for (size_t i = 0; i < size; i++) {
        ((uint16_t *)utf16_data)[i] = (uint16_t)data[i];
    }
    ((uint16_t *)utf16_data)[size] = 0; // Null terminator

    // Bind the UTF-16 text to the prepared statement
    rc = sqlite3_bind_text16(stmt, 1, utf16_data, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        free(utf16_data);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Failed to bind text
    }

    // Execute the prepared statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE && rc != SQLITE_ROW) {
        // Handle execution error if necessary
    }

    // Clean up
    free(utf16_data);
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}