#include <stdint.h>
#include <string.h>  // Include this for strlen
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    const char *text = "sample text";
    sqlite3_uint64 text_len = (sqlite3_uint64)strlen(text);
    unsigned char encoding = SQLITE_UTF8;
    int index = 1;
    int rc;

    // Open a new in-memory database connection
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a table
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare an insert statement
    const char *insert_sql = "INSERT INTO test (value) VALUES (?);";
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    sqlite3_bind_text64(stmt, index, text, text_len, SQLITE_STATIC, encoding);

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Close the database connection
    sqlite3_close(db);

    return 0;
}