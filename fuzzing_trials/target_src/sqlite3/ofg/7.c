#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *tail;
    int rc;
    char *errMsg = 0;

    // Open an in-memory database for testing
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the input data is null-terminated for safe string operations
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Prepare the SQL statement
    rc = sqlite3_prepare_v3(db, sql, -1, 0, &stmt, &tail);

    // Clean up
    if (stmt != NULL) {
        sqlite3_finalize(stmt);
    }
    free(sql);
    sqlite3_close(db);

    return 0;
}

#ifdef __cplusplus
}
#endif