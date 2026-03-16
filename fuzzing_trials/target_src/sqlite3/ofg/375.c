#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_375(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure size is at least 1 to prevent empty input
    if (size > 0) {
        // Use the input data to create a SQL statement
        char *sql = malloc(size + 1);
        if (!sql) {
            sqlite3_close(db);
            return 0;
        }
        memcpy(sql, data, size);
        sql[size] = '\0'; // Null-terminate the string

        // Execute the SQL statement
        rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
        if (rc != SQLITE_OK) {
            sqlite3_free(err_msg);
        }

        free(sql);
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}