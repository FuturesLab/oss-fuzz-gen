#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_276(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    char *errMsg = 0;

    // Open a database connection in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Create a simple table
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    // Insert some data into the table using the fuzzer input
    if (size > 0) {
        char insertSQL[256];
        snprintf(insertSQL, sizeof(insertSQL), "INSERT INTO test (value) VALUES ('%.*s');", (int)size, data);
        rc = sqlite3_exec(db, insertSQL, 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
        }
    }

    // Call the function-under-test
    int changes = sqlite3_total_changes(db);
    printf("Total changes: %d\n", changes);

    // Close the database connection
    sqlite3_close(db);

    return 0;
}