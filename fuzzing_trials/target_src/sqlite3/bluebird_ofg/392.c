#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_392(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc;
    
    // Open a temporary in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement using the input data as SQL
    rc = sqlite3_prepare_v2(db, (const char *)data, size, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement
    rc = sqlite3_step(stmt);

    // Call the function-under-test
    int data_count = sqlite3_data_count(stmt);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}