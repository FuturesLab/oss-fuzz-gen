#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Ensure the data is not NULL and size is greater than 0
    if (data != NULL && size > 0) {
        // Copy data to a new buffer to ensure it is null-terminated
        uint8_t *buffer = (uint8_t *)malloc(size + 1);
        if (buffer == NULL) {
            return 0; // Exit if memory allocation fails
        }
        memcpy(buffer, data, size);
        buffer[size] = '\0'; // Null-terminate the buffer

        // Create a SQLite3 value from the buffer
        sqlite3_value *value;
        sqlite3 *db;
        sqlite3_stmt *stmt;
        int rc = sqlite3_open(":memory:", &db);
        if (rc == SQLITE_OK) {
            rc = sqlite3_prepare_v2(db, "SELECT ?", -1, &stmt, 0);
            if (rc == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, (const char *)buffer, size, SQLITE_TRANSIENT);
                if (sqlite3_step(stmt) == SQLITE_ROW) {
                    value = sqlite3_column_value(stmt, 0);
                    // Call the function-under-test
                    const void *result = sqlite3_value_text16be(value);
                }
                sqlite3_finalize(stmt);
            }
            sqlite3_close(db);
        }

        // Free the buffer
        free(buffer);
    }

    return 0;
}