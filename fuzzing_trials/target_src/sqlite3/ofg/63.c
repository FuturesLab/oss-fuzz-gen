#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    // Ensure the data is not NULL and has a non-zero size
    if (data == NULL || size == 0) {
        return 0;
    }

    // Initialize SQLite database in memory
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Convert data to a null-terminated string
    char *sql = sqlite3_malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0'; // Ensure null-termination

    // Execute the SQL command
    char *errMsg = NULL;
    sqlite3_exec(db, sql, 0, 0, &errMsg);

    // Free resources
    sqlite3_free(sql);
    sqlite3_free(errMsg);
    sqlite3_close(db);

    return 0;
}