#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_473(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errMsg = 0;
    char *sql;
    int rc;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        return 0; // Failed to open database
    }

    // Allocate memory for the SQL statement
    sql = (char *)malloc(size + 1);
    if (sql == NULL) {

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_close with sqlite3_changes
        sqlite3_changes(db);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        return 0; // Memory allocation failed
    }

    // Copy input data to sql and null-terminate it
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute the SQL statement
    rc = sqlite3_exec(db, sql, NULL, NULL, &errMsg);

    // Clean up
    free(sql);
    sqlite3_free(errMsg);
    sqlite3_close(db);

    return 0;
}