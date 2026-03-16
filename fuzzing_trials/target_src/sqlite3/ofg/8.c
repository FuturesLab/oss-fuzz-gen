#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    const char *tail = NULL;
    int rc;

    // Open a temporary in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure data is null-terminated for sqlite3_prepare_v3
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Prepare the SQL statement
    rc = sqlite3_prepare_v3(db, sql, -1, 0, &stmt, &tail);

    // Finalize the statement if it was prepared
    if (stmt != NULL) {
        sqlite3_finalize(stmt);
    }

    // Free the allocated SQL string
    free(sql);

    // Close the database
    sqlite3_close(db);

    return 0;
}