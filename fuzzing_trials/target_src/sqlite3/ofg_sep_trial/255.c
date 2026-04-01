#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_255(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    char *errMsg = NULL;
    int rc;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a dummy table for testing
    rc = sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);", NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare the input as an SQL statement
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    free(sql);

    if (rc == SQLITE_OK && stmt != NULL) {
        // Call the function-under-test
        char *expanded_sql = sqlite3_expanded_sql(stmt);

        // Free the expanded SQL string if it was allocated
        if (expanded_sql != NULL) {
            sqlite3_free(expanded_sql);
        }

        // Finalize the prepared statement
        sqlite3_finalize(stmt);
    }

    // Close the SQLite database
    sqlite3_close(db);

    return 0;
}