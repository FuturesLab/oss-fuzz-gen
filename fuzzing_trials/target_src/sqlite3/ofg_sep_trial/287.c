#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

// Helper function to create a new sqlite3_value and set its value
static sqlite3_value* create_sqlite3_value(const uint8_t *data, size_t size) {
    sqlite3_value *value;
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    // Open a temporary SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return NULL;
    }

    // Prepare a dummy statement to create a value
    rc = sqlite3_prepare_v2(db, "SELECT ?", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return NULL;
    }

    // Bind the data to the statement
    sqlite3_bind_blob(stmt, 1, data, size, SQLITE_TRANSIENT);

    // Get the value from the statement
    value = sqlite3_column_value(stmt, 0);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return value;
}

int LLVMFuzzerTestOneInput_287(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        const char *default_data = "default";
        data = (const uint8_t *)default_data;
        size = strlen(default_data);
    }

    // Create a sqlite3_value object using the helper function
    sqlite3_value *value = create_sqlite3_value(data, size);
    if (!value) {
        return 0;
    }

    // Call the function-under-test
    const void *blob = sqlite3_value_blob(value);

    // Use the returned blob in some way to avoid compiler optimizations removing the call
    if (blob != NULL) {
        volatile const void *use_blob = blob;
        (void)use_blob; // Suppress unused variable warning
    }

    // No need to free value explicitly as it is managed by SQLite
    return 0;
}