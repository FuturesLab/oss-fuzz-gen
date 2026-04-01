#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_358(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Use the input data as an SQL command
    char *errMsg = 0;
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0'; // Null-terminate the string

    // Execute SQL command
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
    }

    free(sql);

    // Call the function-under-test
    int errno_result = sqlite3_system_errno(db);

    // Close the SQLite database
    sqlite3_close(db);

    return 0;
}