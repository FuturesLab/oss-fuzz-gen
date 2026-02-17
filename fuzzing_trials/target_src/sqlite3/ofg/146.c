#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *tail;
    int rc;

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Unable to open database
    }

    // Ensure the input size is manageable for a SQL statement
    if (size > 1000) {
        size = 1000; // Limit the size to prevent overly large statements
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
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &tail);
    
    // Clean up
    free(sql);
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}