#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <stddef.h> // Include for size_t

int LLVMFuzzerTestOneInput_275(const uint8_t *data, size_t size) {
    sqlite3_stmt *stmt = NULL;
    const char *zName = "test_pointer";
    void *pValue = (void *)data; // Use the input data as a pointer
    int rc;
    int index = 1; // Bind index starts at 1 in SQLite

    // Initialize SQLite and prepare a statement
    sqlite3 *db;
    sqlite3_open(":memory:", &db);
    sqlite3_exec(db, "CREATE TABLE test (id INTEGER);", NULL, NULL, NULL);
    sqlite3_prepare_v2(db, "INSERT INTO test (id) VALUES (?);", -1, &stmt, NULL);

    // Call the function under test
    rc = sqlite3_bind_pointer(stmt, index, pValue, zName, NULL);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}