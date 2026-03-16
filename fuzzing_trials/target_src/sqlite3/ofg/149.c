#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    char *errMsg = NULL;
    int rc;

    // Ensure the data is null-terminated to be used as a SQL statement
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Open a new in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        free(sql);
        return 0;
    }

    // Execute the SQL statement
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK && errMsg != NULL) {
        sqlite3_free(errMsg);
    }

    // Call the function-under-test
    sqlite3_int64 lastRowId = sqlite3_last_insert_rowid(db);

    // Clean up
    sqlite3_close(db);
    free(sql);

    return 0;
}