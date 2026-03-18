#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <stdlib.h>  // Include for NULL
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    char *errMsg = NULL;
    int rc;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare an SQL statement using the input data
    // Note: The input data is not null-terminated, so we need to handle it carefully
    char *sql = sqlite3_mprintf("%.*s", (int)size, data);

    // Execute the SQL statement
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    
    // Free the allocated SQL string
    sqlite3_free(sql);

    // Check for errors
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}