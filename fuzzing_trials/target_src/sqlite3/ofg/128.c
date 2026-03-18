#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h> // Include this for malloc and free

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    // Initialize SQLite database
    sqlite3 *db;
    sqlite3_stmt *stmt = NULL;
    const char *tail = NULL;
    int rc;

    // Create an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the input data is null-terminated for use as a SQL statement
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Call the function-under-test
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &tail);

    // Clean up
    if (stmt != NULL) {
        sqlite3_finalize(stmt);
    }
    free(sql);
    sqlite3_close(db);

    return 0;
}