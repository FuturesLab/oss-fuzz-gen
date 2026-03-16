#include <stddef.h>  // For size_t
#include <stdint.h>  // For uint8_t
#include <stdlib.h>  // For NULL, malloc, free
#include "sqlite3.h" // For SQLite functions
#include <string.h>  // For memcpy

// Define a dummy callback function that matches the expected signature
int commit_hook_callback(void *user_data) {
    // This is a simple callback that does nothing
    return 0;
}

int LLVMFuzzerTestOneInput_547(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    void *user_data = (void *)data; // Use the input data as user data

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a table to ensure there is something to commit
    rc = sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Ensure the data is null-terminated before using it in sqlite3_mprintf
    char *null_terminated_data = (char *)malloc(size + 1);
    if (!null_terminated_data) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0'; // Null-terminate the data

    // Insert data into the table using fuzz input
    char *sql = sqlite3_mprintf("INSERT INTO test (value) VALUES ('%q');", null_terminated_data);
    free(null_terminated_data); // Free the temporary buffer
    rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
    sqlite3_free(sql);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    sqlite3_commit_hook(db, commit_hook_callback, user_data);

    // Perform a commit to trigger the commit hook
    rc = sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Cleanup
    sqlite3_close(db);

    return 0;
}