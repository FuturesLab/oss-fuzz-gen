#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt = NULL;
    const char *tail = NULL;
    int rc;

    // Initialize SQLite in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the data is null-terminated for use as a SQL statement
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Call the function-under-test
    rc = sqlite3_prepare_v3(db, sql, (int)size, 0, &stmt, &tail);

    // Clean up
    if (stmt) {
        sqlite3_finalize(stmt);
    }
    free(sql);
    sqlite3_close(db);

    return 0;
}