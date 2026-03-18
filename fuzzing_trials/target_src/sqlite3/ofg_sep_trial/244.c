#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <string.h>  // Include for NULL
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_244(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to create at least one sqlite3_value
    if (size < 1) {
        return 0;
    }

    // Create an SQLite memory context
    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Prepare a statement to bind data
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT ?;", -1, &stmt, NULL);

    // Bind the input data to the statement
    sqlite3_bind_text(stmt, 1, (const char *)data, size, SQLITE_TRANSIENT);

    // Execute the statement
    sqlite3_step(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}