#include <sqlite3.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    sqlite3_stmt *stmt;
    int rc;
    const char *text = (const char *)data;
    int index = 1; // Binding index (1-based)
    sqlite3_uint64 length = size; // Length of the text
    unsigned char type = SQLITE_STATIC; // Binding type

    // Prepare a dummy SQL statement
    const char *sql = "SELECT * FROM test_table WHERE id = ?;";
    rc = sqlite3_prepare_v2(NULL, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return 0; // If preparation fails, exit
    }

    // Ensure the length does not exceed the maximum allowed for bind
    if (length > 0xFFFFFFFF) {
        length = 0xFFFFFFFF; // Cap length to maximum
    }

    // Call the function under test
    rc = sqlite3_bind_text64(stmt, index, text, length, NULL, type);
    
    // Finalize the statement to clean up
    sqlite3_finalize(stmt);

    return 0;
}