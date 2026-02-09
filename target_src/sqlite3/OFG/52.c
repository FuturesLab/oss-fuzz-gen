#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <stdint.h> // Include for uint8_t

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *paramName;
    int paramIndex;

    // Initialize SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple SQL statement
    const char *sql = "SELECT * FROM test WHERE id = :id";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare statement
    }

    // Ensure the size is within the bounds of a valid parameter index
    paramIndex = (size > 0) ? (data[0] % 10) + 1 : 1; // Example: limit to 1-10

    // Call the function under test
    paramName = sqlite3_bind_parameter_name(stmt, paramIndex);
    
    // Optionally print the parameter name for debugging
    if (paramName != NULL) {
        printf("Parameter Name: %s\n", paramName);
    }

    // Cleanup
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}