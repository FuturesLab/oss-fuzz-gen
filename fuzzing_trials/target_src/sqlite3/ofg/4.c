#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_int64 last_insert_rowid;

    // Initialize the SQLite database
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // If database can't be opened, exit
    }

    // Create a simple table
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY AUTOINCREMENT);";
    char *err_msg = NULL;
    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0; // If table creation fails, exit
    }

    // Insert a row into the table
    const char *insert_sql = "INSERT INTO test DEFAULT VALUES;";
    rc = sqlite3_exec(db, insert_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0; // If insert fails, exit
    }

    // Call the function under test
    last_insert_rowid = sqlite3_last_insert_rowid(db);

    // Clean up
    sqlite3_close(db);

    return 0; // Return 0 to indicate successful execution
}