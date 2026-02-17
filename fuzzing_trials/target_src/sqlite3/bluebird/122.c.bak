#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt = NULL;
    const void *tail;
    int rc;

    // Open a temporary in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Prepare the SQL statement using the input data
    // Ensure that size is within a reasonable limit for SQL statement length
    int sql_length = (size > 1000) ? 1000 : (int)size; // Limit to 1000 bytes

    // Convert input data to UTF-16
    // Allocate enough space for the UTF-16 string (2 bytes per character + null terminator)
    size_t utf16_length = sql_length * 2 + 2; // +2 for null terminator
    uint16_t *utf16_data = (uint16_t *)malloc(utf16_length);
    if (!utf16_data) {
        sqlite3_close(db);
        return 0; // Memory allocation failed
    }

    // Convert to UTF-16 (assuming input is ASCII for simplicity)
    for (int i = 0; i < sql_length; i++) {
        utf16_data[i] = (uint16_t)data[i];
    }
    utf16_data[sql_length] = 0; // Null-terminate the UTF-16 string

    // Prepare the SQL statement
    rc = sqlite3_prepare16(db, utf16_data, sql_length * 2 + 2, &stmt, &tail);

    // Clean up
    free(utf16_data); // Free the allocated UTF-16 data
    if (stmt) {
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);

    return 0;
}