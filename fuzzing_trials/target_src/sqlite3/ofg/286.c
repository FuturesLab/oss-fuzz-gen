#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

// Dummy callback function to be used as a commit hook
int commit_hook_callback(void *user_data) {
    // For fuzzing purposes, we can just return 0
    return 0;
}

int LLVMFuzzerTestOneInput_286(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    void *user_data = (void *)data;  // Use the input data as user data

    // Open a temporary in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;  // If opening the database fails, exit early
    }

    // Call the function-under-test
    sqlite3_commit_hook(db, commit_hook_callback, user_data);

    // Close the database
    sqlite3_close(db);

    return 0;
}