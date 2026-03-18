#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_381(const uint8_t *data, size_t size) {
    // Ensure the size is not zero to avoid passing zero to sqlite3_malloc
    if (size == 0) return 0;

    // Initialize SQLite
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a simple SQL statement using the input data
    const char *sql = "CREATE TABLE IF NOT EXISTS fuzz_table(data BLOB);";
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Insert the input data into the table
    sqlite3_stmt *stmt;
    sql = "INSERT INTO fuzz_table(data) VALUES(?);";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data to the SQL statement
    sqlite3_bind_blob(stmt, 1, data, (int)size, SQLITE_STATIC);

    // Execute the statement
    sqlite3_step(stmt);

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Close the database
    sqlite3_close(db);

    return 0;
}