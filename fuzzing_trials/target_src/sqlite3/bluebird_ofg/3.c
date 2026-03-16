#include <stdint.h>
#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errMsg = NULL;
    char **result;
    int rows, columns;
    int rc;

    // Create a copy of the input data and ensure it is null-terminated
    char *sqlQuery = (char *)malloc(size + 1);
    if (sqlQuery == NULL) {
        return 0;
    }
    memcpy(sqlQuery, data, size);
    sqlQuery[size] = '\0';

    // Open a connection to an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        free(sqlQuery);
        return 0;
    }

    // Execute the SQL query using sqlite3_get_table
    rc = sqlite3_get_table(db, sqlQuery, &result, &rows, &columns, &errMsg);

    // Free the result table
    if (result != NULL) {
        sqlite3_free_table(result);
    }

    // Free the error message if it was set
    if (errMsg != NULL) {
        sqlite3_free(errMsg);
    }

    // Close the database connection
    sqlite3_close(db);

    // Free the allocated SQL query
    free(sqlQuery);

    return 0;
}