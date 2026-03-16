#include <sqlite3.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_271(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    char *errMsg = NULL;
    const char *sql = "CREATE TABLE IF NOT EXISTS fuzz_table(id INTEGER PRIMARY KEY, value TEXT);";
    sqlite3_callback callback = NULL;
    void *callbackArg = NULL;

    // Open an in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Execute a basic SQL command to set up the environment
    if (sqlite3_exec(db, sql, callback, callbackArg, &errMsg) != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Ensure the input data is null-terminated for use as a SQL statement
    char *sqlInput = (char *)malloc(size + 1);
    if (sqlInput == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sqlInput, data, size);
    sqlInput[size] = '\0';

    // Fuzz the function-under-test
    sqlite3_exec(db, sqlInput, callback, callbackArg, &errMsg);

    // Clean up
    if (errMsg != NULL) {
        sqlite3_free(errMsg);
    }
    free(sqlInput);
    sqlite3_close(db);

    return 0;
}