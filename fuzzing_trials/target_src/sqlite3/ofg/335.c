#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_335(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to split into two parts
    if (size < 2) return 0;

    // Split the input data into two parts
    size_t str_len = size / 2;
    size_t remaining_size = size - str_len;

    // Create a buffer to hold the string and ensure it's null-terminated
    char str_buffer[str_len + 1];
    memcpy(str_buffer, data, str_len);
    str_buffer[str_len] = '\0';

    // Create a SQLite database in memory
    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Create a prepared statement
    sqlite3_stmt *stmt;
    const char *sql = "SELECT ?"; // Simple query to test with
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    // Bind the blob data to the statement
    sqlite3_bind_blob(stmt, 1, data + str_len, remaining_size, SQLITE_TRANSIENT);

    // Execute the statement
    sqlite3_step(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}