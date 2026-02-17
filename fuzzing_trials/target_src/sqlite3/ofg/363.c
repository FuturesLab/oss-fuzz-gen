#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_363(const uint8_t *data, size_t size) {
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "INSERT INTO test_table (text_column) VALUES (?);";
    int index = 1; // Parameter index for the SQL statement
    int text_length = size > 0 ? (int)size : 1; // Ensure length is at least 1
    const void *text_value = data; // Bind the input data

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(NULL, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return 0; // Failed to prepare statement
    }

    // Bind the text value to the prepared statement
    rc = sqlite3_bind_text16(stmt, index, text_value, text_length, SQLITE_TRANSIENT);
    
    // Finalize the statement to clean up
    sqlite3_finalize(stmt);

    return 0;
}