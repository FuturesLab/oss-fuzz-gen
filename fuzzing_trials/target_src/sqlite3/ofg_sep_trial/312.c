#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_312(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Convert the input data to a null-terminated string
    char *sql = strndup((const char *)data, size);
    if (!sql) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the SQL command
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        sqlite3_free(err_msg);
    }

    // Clean up
    free(sql);
    sqlite3_close(db);

    return 0;
}