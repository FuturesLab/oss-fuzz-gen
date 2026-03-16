#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_369(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    sqlite3 *db = NULL;
    char *errMsg = NULL;
    int rc;

    // Open an in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // If opening the database fails, return early
    }

    // Create a table
    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS fuzz_table (id INTEGER PRIMARY KEY, data BLOB);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare an SQL statement to insert data
    sqlite3_stmt *stmt;
    const char *insertSQL = "INSERT INTO fuzz_table (data) VALUES (?);";
    rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the fuzz input data to the SQL statement
    sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC);

    // Execute the SQL statement
    sqlite3_step(stmt);

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Close the database
    sqlite3_close(db);

    return 0;
}