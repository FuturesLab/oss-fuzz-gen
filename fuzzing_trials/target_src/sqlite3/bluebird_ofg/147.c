#include <stdint.h>
#include "sqlite3.h"
#include <stdlib.h>

int LLVMFuzzerTestOneInput_147(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    char *errMsg = 0;
    sqlite3_int64 changes;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, createTableSQL, NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Insert some data
    const char *insertSQL = "INSERT INTO test (value) VALUES ('test');";
    rc = sqlite3_exec(db, insertSQL, NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Attempt to execute the input data as an SQL statement
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0'; // Null-terminate the string

    rc = sqlite3_exec(db, sql, NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
    }
    free(sql);

    // Call the function-under-test
    changes = sqlite3_changes64(db);

    // Clean up
    sqlite3_close(db);

    return 0;
}