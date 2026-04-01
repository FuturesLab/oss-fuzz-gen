#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_311(const uint8_t *data, size_t size) {
    // Check if size is sufficient for meaningful input
    if (size > 0) {
        // Open an in-memory SQLite database
        sqlite3 *db;
        int rc = sqlite3_open(":memory:", &db);
        if (rc != SQLITE_OK) {
            return 0;
        }

        // Use the data to enable or disable extensions
        rc = sqlite3_enable_load_extension(db, (int)(data[0] % 2));
        if (rc != SQLITE_OK) {
            sqlite3_close(db);
            return 0;
        }

        // Prepare a SQL statement from the input data
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, (const char *)data, size, &stmt, NULL);
        if (rc == SQLITE_OK) {
            // Execute the SQL statement
            sqlite3_step(stmt);
            // Finalize the statement to clean up
            sqlite3_finalize(stmt);
        }

        // Call the function under test
        sqlite3_reset_auto_extension();

        // Close the database connection
        sqlite3_close(db);
    }

    return 0;
}