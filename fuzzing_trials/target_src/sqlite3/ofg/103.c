#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    const char *tail = NULL;
    int rc;
    const char *sql;

    // Initialize the SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Ensure the input data is null-terminated for SQL statement
    size_t sql_length = size < 1024 ? size : 1023; // Limit to prevent buffer overflow
    char *sql_buffer = (char *)malloc(sql_length + 1);
    if (sql_buffer == NULL) {
        sqlite3_close(db);
        return 0; // Memory allocation failed
    }
    memcpy(sql_buffer, data, sql_length);
    sql_buffer[sql_length] = '\0'; // Null-terminate the SQL statement

    // Prepare the SQL statement
    rc = sqlite3_prepare_v3(db, sql_buffer, -1, 0, &stmt, &tail);
    
    // Clean up
    free(sql_buffer);
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0; // Return success
}