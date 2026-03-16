#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_213(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;

    // Open a temporary in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare an SQL statement using the input data
    char *sql = sqlite3_mprintf("%.*s", (int)size, data);
    char *errMsg = NULL;

    // Execute the SQL statement
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        // Handle error if needed
        sqlite3_free(errMsg);
    }

    // Free the allocated SQL string
    sqlite3_free(sql);

    // Call the function-under-test
    int errcode = sqlite3_extended_errcode(db);

    // Use the errcode to avoid compiler optimizations
    if (errcode == SQLITE_OK) {
        // Do something if needed
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}