#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_586(const uint8_t *data, size_t size) {
    // Initialize SQLite database
    sqlite3 *db;
    char *errMsg = 0;

    // Open an in-memory SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Ensure the input data is null-terminated
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute the SQL statement
    sqlite3_exec(db, sql, 0, 0, &errMsg);

    // Free allocated resources
    if (errMsg) {
        sqlite3_free(errMsg);
    }
    free(sql);

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_close with sqlite3_close_v2

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_close_v2 with sqlite3_close
    sqlite3_close(db);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    return 0;
}