#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include string.h for memcmp
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_307(const uint8_t *data, size_t size) {
    // Ensure the size is reasonable for creating a sqlite3_value
    if (size < 1 || size > 1024) {
        return 0;
    }

    // Create a sqlite3 database and prepare a statement
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a temporary table to store the blob
    const char *create_table_sql = "CREATE TABLE temp_table (data BLOB)";
    if (sqlite3_exec(db, create_table_sql, 0, 0, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to create table
    }

    // Prepare a statement to insert the blob
    const char *insert_sql = "INSERT INTO temp_table (data) VALUES (?)";
    if (sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare insert statement
    }

    // Bind the input data as a blob
    sqlite3_bind_blob(stmt, 1, data, size, SQLITE_TRANSIENT);

    // Execute the statement to insert the blob
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0; // Failed to execute insert statement
    }

    // Finalize the insert statement
    sqlite3_finalize(stmt);

    // Prepare a statement to select the blob back
    const char *select_sql = "SELECT data FROM temp_table";
    if (sqlite3_prepare_v2(db, select_sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Failed to prepare select statement
    }

    // Execute the select statement
    int result = sqlite3_step(stmt);

    // Check if the result is SQLITE_ROW and validate the blob
    if (result == SQLITE_ROW) {
        const void *retrieved_data = sqlite3_column_blob(stmt, 0);
        int retrieved_size = sqlite3_column_bytes(stmt, 0);

        // Compare the original data with the retrieved data
        if (retrieved_size == size && memcmp(data, retrieved_data, size) == 0) {
            // Data matches, indicating successful round-trip
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return 1; // Indicate success
        }
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0; // Indicate failure
}