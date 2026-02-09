#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0; // Exit early if there is no input data
    }

    sqlite3_stmt *stmt;
    int rc;
    const char *text = (const char *)data; // Cast data to const char*
    int index = 1; // Bind parameter index (1-based)
    sqlite3_uint64 length = (sqlite3_uint64)size; // Length of the text
    unsigned char encoding = SQLITE_UTF8; // Use UTF-8 encoding

    // Prepare a simple SQL statement for binding
    const char *sql = "INSERT INTO test_table (text_column) VALUES (?);";
    sqlite3 *db;
    sqlite3_open(":memory:", &db); // Open an in-memory database
    sqlite3_exec(db, "CREATE TABLE test_table (text_column TEXT);", 0, 0, 0); // Create a test table

    // Prepare the statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0; // Exit if preparation fails
    }

    // Call the function under test
    rc = sqlite3_bind_text64(stmt, index, text, length, SQLITE_STATIC, encoding);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0; // Return 0 to indicate successful execution
}