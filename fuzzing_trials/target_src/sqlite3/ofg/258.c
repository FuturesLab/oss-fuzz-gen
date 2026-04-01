#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_258(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *errMsg = 0;
    int rc;

    if (size == 0) {
        return 0;
    }

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        return 0;
    }

    // Create a simple table
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement using the input data
    const uint8_t *sqlData = data;
    size_t sqlSize = size;
    char *sql = (char *)malloc(sqlSize + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, sqlData, sqlSize);
    sql[sqlSize] = '\0';

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    free(sql);

    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    char *expandedSQL = sqlite3_expanded_sql(stmt);
    if (expandedSQL != NULL) {
        sqlite3_free(expandedSQL);
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}