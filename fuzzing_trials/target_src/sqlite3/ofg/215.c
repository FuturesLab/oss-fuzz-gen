#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>

// Fuzzing harness for sqlite3_extended_errcode
int LLVMFuzzerTestOneInput_215(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    char *errMsg = 0;

    // Initialize a database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Create a simple table
    rc = sqlite3_exec(db, "CREATE TABLE test (id INT, value TEXT);", NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    // Use the input data to form a SQL statement
    if (size > 0) {
        char sql[256];
        snprintf(sql, sizeof(sql), "INSERT INTO test (id, value) VALUES (%d, '%.*s');", data[0], (int)(size - 1), data + 1);

        // Execute the SQL statement
        rc = sqlite3_exec(db, sql, NULL, 0, &errMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
        }
    }

    // Call the function-under-test
    int extended_errcode = sqlite3_extended_errcode(db);
    (void)extended_errcode; // Use the result to avoid unused variable warning

    // Close the database
    sqlite3_close(db);

    return 0;
}