#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_380(const uint8_t *data, size_t size) {
    // Ensure that the size is not zero
    if (size == 0) {
        return 0;
    }

    sqlite3 *db;
    char *err_msg = 0;

    // Open an in-memory SQLite database
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a table
    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS fuzz_table(data BLOB);";
    rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare an SQL statement for inserting data
    sqlite3_stmt *stmt;
    const char *sql_insert = "INSERT INTO fuzz_table(data) VALUES(?);";
    rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data to the SQL statement
    rc = sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the SQL statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Close the database connection
    sqlite3_close(db);

    return 0;
}