#include <stdlib.h>
#include <string.h> // Include for memcpy
#include <stdint.h> // Include for uint8_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    // Allocate memory based on the input size
    void *ptr = NULL;

    // Ensure that the size is reasonable for allocation
    if (size > 0) {
        ptr = sqlite3_malloc(size);
        if (ptr == NULL) {
            return 0; // Allocation failed, exit early
        }

        // Copy the input data into the allocated memory
        memcpy(ptr, data, size);
    }

    // Create a new SQLite database in memory
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) == SQLITE_OK) {
        // Prepare a simple SQL statement using the input data
        char *errMsg = 0;
        char sql[256];
        snprintf(sql, sizeof(sql), "CREATE TABLE test_table(data BLOB); INSERT INTO test_table(data) VALUES(?);");

        sqlite3_stmt *stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            // Bind the input data to the SQL statement
            sqlite3_bind_blob(stmt, 1, ptr, size, SQLITE_STATIC);

            // Execute the statement
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }

        // Close the database
        sqlite3_close(db);
    }

    // Free the allocated memory
    sqlite3_free(ptr);

    return 0;
}