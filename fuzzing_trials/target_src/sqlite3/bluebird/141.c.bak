#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h> // Include for strlen

int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    const char *sql = (const char *)data; // Treat input data as SQL statement
    int rc;

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Prepare the SQL statement
    // Ensure the input is null-terminated for sqlite3_prepare_v2
    size_t sql_length = size < SQLITE_MAX_LENGTH ? size : SQLITE_MAX_LENGTH;
    char *sql_copy = (char *)malloc(sql_length + 1);
    if (sql_copy == NULL) {
        sqlite3_close(db);
        return 0; // Memory allocation failed
    }
    memcpy(sql_copy, sql, sql_length);
    sql_copy[sql_length] = '\0'; // Null-terminate the string

    rc = sqlite3_prepare_v2(db, sql_copy, -1, &stmt, NULL);
    free(sql_copy); // Free the allocated memory for the SQL copy
    if (rc != SQLITE_OK) {
        // Cleanup if preparation fails
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Finalize the statement to clean up
    sqlite3_finalize(stmt);
    // Close the database connection
    sqlite3_close(db);

    return 0; // Successful execution
}