#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

// Define a custom destructor_2 function
void custom_destructor_2(void *ptr) {
    // Custom cleanup code, if necessary
    (void)ptr; // Suppress unused variable warning
}

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    // Open a new in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table
    const char *create_table_sql = "CREATE TABLE test (id INTEGER, value TEXT);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare an SQL statement for binding
    const char *sql = "INSERT INTO test (id, value) VALUES (?, ?);";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind an integer to the first parameter
    sqlite3_bind_int(stmt, 1, 1);

    // Bind the fuzzing input to the second parameter using sqlite3_bind_text64
    sqlite3_uint64 text_length = (sqlite3_uint64)size;
    unsigned char encoding = SQLITE_UTF8;
    sqlite3_bind_text64(stmt, 2, (const char *)data, text_length, custom_destructor_2, encoding);

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Close the database
    sqlite3_close(db);

    return 0;
}