#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_178(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    const void *tail = NULL;
    int rc;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Ensure the size does not exceed maximum allowed length
    if (size > SQLITE_MAX_SQL_LENGTH) {
        size = SQLITE_MAX_SQL_LENGTH;
    }

    // Convert input data to UTF-16
    // Allocate memory for the UTF-16 string
    size_t utf16_size = (size + 1) * 2; // +1 for null terminator
    uint16_t *utf16_data = (uint16_t *)malloc(utf16_size);
    if (!utf16_data) {
        sqlite3_close(db);
        return 0; // Memory allocation failed
    }

    // Convert to UTF-16 (assuming input is ASCII for simplicity)
    for (size_t i = 0; i < size; i++) {
        utf16_data[i] = (uint16_t)data[i];
    }
    utf16_data[size] = 0; // Null-terminate the UTF-16 string

    // Call the function under test
    rc = sqlite3_prepare16_v2(db, utf16_data, (int)(utf16_size), &stmt, &tail);

    // Finalize the statement to avoid memory leaks
    if (stmt) {
        sqlite3_finalize(stmt);
    }

    // Free the allocated UTF-16 data
    free(utf16_data);

    // Close the database connection
    sqlite3_close(db);

    return 0;
}