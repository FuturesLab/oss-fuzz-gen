#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h> // Include for memcpy
#include <stdlib.h> // Include for malloc and free

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    const char *tail = NULL;
    int rc;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Ensure the input size is manageable
    if (size > 1000) {
        size = 1000; // Limit the size for the SQL statement
    }

    // Create a null-terminated string from the input data
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0; // Memory allocation failed
    }
    memcpy(sql, data, size);
    sql[size] = '\0'; // Null-terminate the string

    // Prepare the SQL statement
    rc = sqlite3_prepare_v3(db, sql, -1, 0, &stmt, &tail);
    
    // Clean up
    free(sql);
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0; // Return 0 to indicate successful execution
}