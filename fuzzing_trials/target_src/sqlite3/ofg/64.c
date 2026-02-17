#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    int logLevel = 1; // Example log level
    sqlite3 *db;
    char *errMsg = 0;

    // Ensure the data is not too large for a message
    if (size > 1024) {
        size = 1024; // Limit the size to avoid buffer overflow
    }

    // Allocate memory for the message and ensure it's not NULL
    char *messageBuffer = (char *)malloc(size + 20); // Allocate extra space for formatting
    if (messageBuffer == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Create a formatted message
    snprintf(messageBuffer, size + 20, "Fuzz input: %.*s", (int)size, data);

    // Open a temporary SQLite database in memory
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        free(messageBuffer);
        return 0; // Exit if database opening fails
    }

    // Create a simple table to insert the message
    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS fuzz_data (id INTEGER PRIMARY KEY, message TEXT);";
    sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);

    // Prepare and execute the SQL statement to insert the message
    const char *insertSQL = "INSERT INTO fuzz_data (message) VALUES (?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, messageBuffer, -1, SQLITE_STATIC);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    // Clean up
    sqlite3_close(db);
    free(messageBuffer);

    return 0;
}