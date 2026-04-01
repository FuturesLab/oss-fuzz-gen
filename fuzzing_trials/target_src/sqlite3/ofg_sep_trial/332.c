#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_332(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    
    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a dummy table
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare an SQL statement
    const char *sql = "INSERT INTO test (value) VALUES (?);";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Ensure the data is null-terminated
    char *text = (char *)malloc(size + 1);
    if (text == NULL) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }
    memcpy(text, data, size);
    text[size] = '\0';

    // Call the function-under-test
    sqlite3_bind_text(stmt, 1, text, -1, SQLITE_TRANSIENT);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    free(text);

    return 0;
}