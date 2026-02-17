#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *tail;
    int rc;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Prepare the SQL statement
    // Ensure that the input size does not exceed a reasonable limit
    if (size > 1000) {
        size = 1000;
    }

    // Create a null-terminated string from the input data
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0; // Memory allocation failed
    }
    memcpy(sql, data, size);
    sql[size] = '\0'; // Null-terminate the string

    // Call the function under test
    rc = sqlite3_prepare(db, sql, -1, &stmt, &tail);

    // Free the prepared statement
    if (stmt) {
        sqlite3_finalize(stmt);
    }

    // Free the SQL string
    free(sql);

    // Close the database
    sqlite3_close(db);

    return 0; // Return success
}