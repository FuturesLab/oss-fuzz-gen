#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_622(const uint8_t *data, size_t size) {
    // Initialize SQLite3
    sqlite3_initialize();

    // Create a new SQLite database in memory
    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Ensure the data is not NULL and has a valid size
    if (data != NULL && size > 0) {
        // Create a SQL statement from the input data
        // Ensure the data is null-terminated to prevent buffer overflow
        char *sql = (char *)malloc(size + 1);
        if (sql) {
            memcpy(sql, data, size);
            sql[size] = '\0'; // Null-terminate the string

            char *errMsg = 0;
            sqlite3_exec(db, sql, 0, 0, &errMsg);
            
            // If there was an error, free the error message
            if (errMsg) {
                sqlite3_free(errMsg);
            }
            free(sql);
        }
    } else {
        // If data is NULL or size is 0, execute a default SQL statement
        const char *defaultData = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
        char *errMsg = 0;
        sqlite3_exec(db, defaultData, 0, 0, &errMsg);
        
        // If there was an error, free the error message
        if (errMsg) {
            sqlite3_free(errMsg);
        }
    }

    // Close the SQLite database
    sqlite3_close(db);

    // Finalize SQLite3
    sqlite3_shutdown();

    return 0;
}