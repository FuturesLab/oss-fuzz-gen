#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free

int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a simple statement
    const char *sql = "INSERT INTO test (value) VALUES (?);";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Ensure the data is null-terminated
    char *parameterName = (char *)malloc(size + 1);
    if (parameterName == NULL) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }
    memcpy(parameterName, data, size);
    parameterName[size] = '\0';

    // Call the function-under-test
    sqlite3_bind_parameter_index(stmt, parameterName);

    // Clean up
    free(parameterName);
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}