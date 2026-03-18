#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_193(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    char *errMsg = 0;

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure null-terminated string for SQL statement
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        // Call the function under test
        const char *original_sql = sqlite3_sql(stmt);

        // Use the result in some way to avoid compiler optimizations
        if (original_sql != NULL) {
            (void)strlen(original_sql);
        }

        // Finalize the statement
        sqlite3_finalize(stmt);
    }

    // Clean up
    free(sql);
    sqlite3_close(db);

    return 0;
}