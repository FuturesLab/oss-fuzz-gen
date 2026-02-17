#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_274(const uint8_t *data, size_t size) {
    sqlite3_stmt *stmt;
    int rc;
    int index = 1; // Assuming we want to bind to the first parameter
    int id = 0; // Variable to hold the integer id from the input data

    // Ensure the size is sufficient to read an integer
    if (size >= sizeof(int)) {
        // Convert the first few bytes of data to an integer
        id = *((int*)data);
    }

    // Prepare a simple SQL statement
    const char *sql = "SELECT * FROM test_table WHERE id = ?;";
    rc = sqlite3_prepare_v2(NULL, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return 0; // Failed to prepare statement
    }

    // Bind the integer id to the SQL statement
    rc = sqlite3_bind_int(stmt, index, id);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return 0; // Failed to bind parameter
    }

    // Execute the statement (this will invoke the function under test)
    rc = sqlite3_step(stmt);
    
    // Finalize the statement
    sqlite3_finalize(stmt);

    return 0;
}