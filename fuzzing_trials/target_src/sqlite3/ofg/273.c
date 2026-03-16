#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>

// Remove the 'extern "C"' linkage specification for C++ since this is C code
int LLVMFuzzerTestOneInput_273(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    char *errMsg = 0;

    // Open a new in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Execute a simple SQL statement to ensure there are changes
    rc = sqlite3_exec(db, "CREATE TABLE test (id INT); INSERT INTO test (id) VALUES (1);", 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    int changes = sqlite3_total_changes(db);
    printf("Total changes: %d\n", changes);

    // Close the database
    sqlite3_close(db);

    return 0;
}