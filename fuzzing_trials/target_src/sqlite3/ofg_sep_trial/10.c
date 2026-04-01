#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>  // Include for malloc and free

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt = NULL;
    const void *tail = NULL;
    int rc;

    // Initialize an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the data is null-terminated for sqlite3_prepare16
    void *sql = malloc(size + 2);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    ((uint16_t *)sql)[size / 2] = 0;  // Null-terminate as UTF-16

    // Call the function-under-test
    sqlite3_prepare16(db, sql, (int)size, &stmt, &tail);

    // Clean up
    if (stmt != NULL) {
        sqlite3_finalize(stmt);
    }
    free(sql);
    sqlite3_close(db);

    return 0;
}