#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_279(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "INSERT INTO test_table (text_column) VALUES (?);";
    
    // Open a database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a table for testing
    rc = sqlite3_exec(db, "CREATE TABLE test_table (text_column TEXT);", 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Ensure the size is not too large for binding
    int bind_size = (size > 100) ? 100 : (int)size; // Limit to 100 characters
    char *text_to_bind = (char *)malloc(bind_size + 1);
    if (text_to_bind == NULL) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Memory allocation failed
    }

    // Copy data to a string and null-terminate it
    memcpy(text_to_bind, data, bind_size);
    text_to_bind[bind_size] = '\0';

    // Bind the text to the prepared statement
    rc = sqlite3_bind_text(stmt, 1, text_to_bind, -1, SQLITE_STATIC);
    
    // Clean up
    free(text_to_bind);
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}