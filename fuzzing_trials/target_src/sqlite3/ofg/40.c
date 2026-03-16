#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt = NULL;
    int rc;
    
    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the input data is null-terminated for SQLite
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK && stmt != NULL) {
        // Finalize the statement
        sqlite3_finalize(stmt);
    }

    // Clean up
    free(sql);
    sqlite3_close(db);

    return 0;
}