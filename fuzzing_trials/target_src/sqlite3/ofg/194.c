#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_194(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    char *errMsg = 0;

    // Initialize SQLite in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the input data is null-terminated
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
        // Call the function-under-test
        const char *sqlString = sqlite3_sql(stmt);

        // Use the result to prevent optimization out
        if (sqlString != NULL) {
            volatile char dummy = sqlString[0];
            (void)dummy;
        }

        // Finalize the statement
        sqlite3_finalize(stmt);
    }

    // Clean up
    free(sql);
    sqlite3_close(db);

    return 0;
}