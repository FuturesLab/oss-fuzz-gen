#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_266(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    char *errMsg = 0;
    char *sql;
    
    // Initialize an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Create a simple table
    sql = "CREATE TABLE IF NOT EXISTS test(id INT, value TEXT);";
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare the input data as an SQL statement
    char *inputSQL = (char *)malloc(size + 1);
    if (inputSQL == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(inputSQL, data, size);
    inputSQL[size] = '\0';

    // Execute the input SQL statement
    rc = sqlite3_exec(db, inputSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK && errMsg != NULL) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    // Call the function-under-test
    int changes = sqlite3_changes(db);
    printf("Number of changes: %d\n", changes);

    // Clean up
    free(inputSQL);
    sqlite3_close(db);

    return 0;
}