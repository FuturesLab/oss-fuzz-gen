#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h> // Include this for malloc and free

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    // Ensure the data is null-terminated
    char *sql = (char *)malloc(size + 1);
    if (!sql) return 0;
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        free(sql);
        return 0;
    }

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        // Call the function-under-test
        int param_count = sqlite3_bind_parameter_count(stmt);

        // Clean up
        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
    free(sql);

    return 0;
}