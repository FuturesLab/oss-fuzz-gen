#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <stdlib.h>  // Include for NULL
#include <sqlite3.h>

// Ensure to include extern "C" if using C++
// extern "C" 
int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    char *errMsg = 0;

    // Initialize the SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table
    const char *sqlCreateTable = "CREATE TABLE test(id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, sqlCreateTable, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Insert a row into the table
    const char *sqlInsert = "INSERT INTO test (value) VALUES ('test');";
    rc = sqlite3_exec(db, sqlInsert, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    sqlite3_int64 lastRowId = sqlite3_last_insert_rowid(db);

    // Clean up
    sqlite3_close(db);

    return 0;
}