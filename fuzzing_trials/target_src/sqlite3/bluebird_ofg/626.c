#include <stdint.h>
#include "sqlite3.h"
#include <stddef.h>

int LLVMFuzzerTestOneInput_626(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    sqlite3_int64 lastRowId;

    // Open a new in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a table and insert a row to ensure there is a last insert row id
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    const char *insertSQL = "INSERT INTO test (value) VALUES ('test');";
    sqlite3_exec(db, createTableSQL, 0, 0, 0);
    sqlite3_exec(db, insertSQL, 0, 0, 0);

    // Call the function-under-test
    lastRowId = sqlite3_last_insert_rowid(db);

    // Clean up
    sqlite3_close(db);

    return 0;
}