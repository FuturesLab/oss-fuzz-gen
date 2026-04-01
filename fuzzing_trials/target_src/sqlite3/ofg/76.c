#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER, name TEXT); INSERT INTO test (id, name) VALUES (1, 'Alice');";
    const char *tail;
    const char *decl_type;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Execute SQL statement to create table and insert data
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement to select from the table
    rc = sqlite3_prepare_v2(db, "SELECT * FROM test;", -1, &stmt, &tail);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    // Ensure the index is within the bounds of the number of columns
    int column_index = size > 0 ? data[0] % sqlite3_column_count(stmt) : 0;

    // Call the function-under-test
    decl_type = sqlite3_column_decltype(stmt, column_index);

    // Print the result for debugging purposes
    if (decl_type != NULL) {
        printf("Column declaration type: %s\n", decl_type);
    } else {
        printf("Column declaration type is NULL\n");
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}