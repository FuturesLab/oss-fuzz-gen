#include <stdint.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_632(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc;
    char *errMsg = NULL;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER, name TEXT);";
    const char *query = "SELECT * FROM test;";
    const char *columnType;
    int columnIndex;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Execute SQL to create a table
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Ensure the data size is sufficient to extract an integer index
    if (size < sizeof(int)) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Use the first 4 bytes of data as an integer index
    memcpy(&columnIndex, data, sizeof(int));

    // Call the function-under-test
    columnType = sqlite3_column_decltype(stmt, columnIndex);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}