#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <stdio.h> // Include stdio.h for snprintf

int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_int64 changes;

    // Initialize a SQLite database in memory
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple table to ensure there are changes to count
    const char *create_table_sql = "CREATE TABLE test(id INTEGER PRIMARY KEY, value TEXT);";
    sqlite3_exec(db, create_table_sql, 0, 0, 0);

    // Insert data into the table using the input data
    // Limit the size of the input to prevent overly large SQL statements
    size_t sql_size = size < 100 ? size : 100; // Limit to 100 bytes
    char *insert_sql = (char *)malloc(sql_size + 50); // Allocate memory for the SQL statement
    snprintf(insert_sql, sql_size + 50, "INSERT INTO test(value) VALUES('%.*s');", (int)sql_size, data);

    // Execute the insert statement
    sqlite3_exec(db, insert_sql, 0, 0, 0);

    // Call the function under test
    changes = sqlite3_total_changes64(db);

    // Clean up
    free(insert_sql);
    sqlite3_close(db);

    return 0;
}