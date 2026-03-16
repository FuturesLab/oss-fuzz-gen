#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_254(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *expanded_sql;
    int rc;

    // Initialize the SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the data is null-terminated for SQLite to process it as a string
    char *sql = (char *)sqlite3_malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_free(sql);
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    expanded_sql = sqlite3_expanded_sql(stmt);

    // Clean up
    sqlite3_free(expanded_sql);
    sqlite3_finalize(stmt);
    sqlite3_free(sql);
    sqlite3_close(db);

    return 0;
}