#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    char *errMsg = 0;
    const char *sql = "CREATE TABLE IF NOT EXISTS test(id INT, value TEXT);";

    // Open a new in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Execute SQL to create a table
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement from the input data
    rc = sqlite3_prepare_v2(db, (const char *)data, size, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind an integer to the first parameter if possible
    if (sqlite3_bind_parameter_count(stmt) > 0) {
        sqlite3_bind_int(stmt, 1, 1);
    }

    // Step through the results
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Call the function-under-test
        int columnType = sqlite3_column_type(stmt, 0);
        (void)columnType;  // Use the result to prevent unused variable warning
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}