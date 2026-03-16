#include <stdint.h>
#include <stddef.h>  // Include this for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_262(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    char *errMsg = 0;

    // Open a new in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        sqlite3_close(db);
        return 0;
    }

    // Create a simple table
    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Use the input data to insert into the table
    char insertSQL[256];
    snprintf(insertSQL, sizeof(insertSQL), "INSERT INTO test (value) VALUES ('%.*s');", (int)size, data);
    rc = sqlite3_exec(db, insertSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    int changes = sqlite3_changes(db);

    // Clean up
    sqlite3_close(db);

    return 0;
}