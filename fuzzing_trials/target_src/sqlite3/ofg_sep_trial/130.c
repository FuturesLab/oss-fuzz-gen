#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    // Open a new in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure that size is at least 1 to use data[0] safely
    if (size > 0) {
        // Use the first byte of data to determine the value of onoff
        int onoff = data[0] % 2; // This will be either 0 or 1

        // Call the function-under-test
        sqlite3_extended_result_codes(db, onoff);
    }

    // Use the input data as a SQL statement
    if (size > 1) {
        // Create a null-terminated string from the input data
        char *sql = (char *)malloc(size + 1);
        if (sql != NULL) {
            memcpy(sql, data + 1, size - 1);
            sql[size - 1] = '\0';

            // Execute the SQL statement
            sqlite3_exec(db, sql, 0, 0, &errMsg);

            // Free the allocated memory
            free(sql);
        }
    }

    // Close the database connection
    sqlite3_close(db);

    return 0;
}