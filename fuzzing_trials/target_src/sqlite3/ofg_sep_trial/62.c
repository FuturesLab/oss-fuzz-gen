#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    // Ensure the data size is non-zero to avoid passing NULL to sqlite3_exec
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *sql = sqlite3_malloc(size + 1);
    if (sql == NULL) {
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';  // Null-terminate the string

    // Open an in-memory SQLite database
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        sqlite3_free(sql);
        return 0;
    }

    // Execute the SQL command
    char *errMsg = NULL;
    sqlite3_exec(db, sql, 0, 0, &errMsg);

    // Free the error message if it was allocated
    if (errMsg != NULL) {
        sqlite3_free(errMsg);
    }

    // Close the database
    sqlite3_close(db);

    // Free the allocated memory for the SQL command
    sqlite3_free(sql);

    return 0;
}