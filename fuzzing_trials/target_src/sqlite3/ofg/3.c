#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a custom destructor function
void custom_destructor_3(void *ptr) {
    // Free the memory if it was dynamically allocated
    if (ptr) {
        free(ptr);
    }
}

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Initialize SQLite
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare an insert statement
    const char *insert_sql = "INSERT INTO test (value) VALUES (?);";
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Ensure the data is null-terminated
    char *text = (char *)malloc(size + 1);
    if (text == NULL) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }
    memcpy(text, data, size);
    text[size] = '\0';

    // Bind the text to the statement
    sqlite3_uint64 text_length = (sqlite3_uint64)size;
    unsigned char encoding = SQLITE_UTF8; // Use UTF-8 encoding
    rc = sqlite3_bind_text64(stmt, 1, text, text_length, custom_destructor_3, encoding);

    // Execute the statement
    if (rc == SQLITE_OK) {
        sqlite3_step(stmt);
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}