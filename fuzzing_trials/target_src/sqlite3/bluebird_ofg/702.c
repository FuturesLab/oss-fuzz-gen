#include <stddef.h>  // For size_t and NULL
#include <stdint.h>
#include "sqlite3.h"
#include <assert.h>

int LLVMFuzzerTestOneInput_702(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    sqlite3_int64 changes;

    // Open a new in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    assert(rc == SQLITE_OK);

    // Create a simple table
    rc = sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);", NULL, NULL, NULL);
    assert(rc == SQLITE_OK);

    // Insert some data into the table
    rc = sqlite3_exec(db, "INSERT INTO test (value) VALUES ('A');", NULL, NULL, NULL);
    assert(rc == SQLITE_OK);

    // Call the function-under-test
    changes = sqlite3_total_changes64(db);

    // Ensure that the function returns a non-negative value
    assert(changes >= 0);

    // Clean up and close the database
    sqlite3_close(db);

    return 0;
}