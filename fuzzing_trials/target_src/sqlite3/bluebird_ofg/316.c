#include <stdint.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <string.h>

// Define a custom destructor function to match the signature required
void custom_destructor_316(void *ptr) {
    // Free the memory allocated for the blob
    free(ptr);
}

int LLVMFuzzerTestOneInput_316(const uint8_t *data, size_t size) {
    // Allocate memory for the blob and copy the data into it
    void *blob = malloc(size);
    if (blob == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(blob, data, size);

    // Define a sqlite3_uint64 size for the blob
    sqlite3_uint64 blob_size = (sqlite3_uint64)size;

    // Initialize SQLite and create a database in memory
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        free(blob);
        return 0;
    }

    // Create a table to store the blob
    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS fuzz_table (data BLOB);";
    if (sqlite3_exec(db, create_table_sql, 0, 0, 0) != SQLITE_OK) {
        sqlite3_close(db);
        free(blob);
        return 0;
    }

    // Prepare a statement to insert the blob into the table
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, "INSERT INTO fuzz_table (data) VALUES (?);", -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        free(blob);
        return 0;
    }

    // Bind the blob to the statement
    sqlite3_bind_blob64(stmt, 1, blob, blob_size, custom_destructor_316);

    // Step through the statement to execute it
    sqlite3_step(stmt);

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Prepare a statement to query the blob back
    if (sqlite3_prepare_v2(db, "SELECT data FROM fuzz_table;", -1, &stmt, NULL) == SQLITE_OK) {
        // Execute the query and step through the results
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            // Access the blob data if needed
            const void *retrieved_blob = sqlite3_column_blob(stmt, 0);
            int retrieved_blob_size = sqlite3_column_bytes(stmt, 0);
            // Optionally, do something with retrieved_blob and retrieved_blob_size
        }
        sqlite3_finalize(stmt);
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}