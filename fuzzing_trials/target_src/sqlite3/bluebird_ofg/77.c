#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    // Initialize a SQLite database connection
    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db); // Create an in-memory database
    if (rc != SQLITE_OK) {
        return 0; // If we can't open the database, exit early
    }

    // Prepare a statement to create a table
    const char *sql_create_table = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    char *errMsg = 0;
    rc = sqlite3_exec(db, sql_create_table, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg); // Free the error message if there is one
        sqlite3_close(db); // Close the database connection
        return 0; // Exit if table creation failed
    }

    // Use the input data to insert a value into the table
    // Ensure the data is null-terminated for SQLite
    char *input_value = (char *)malloc(size + 1);
    if (input_value == NULL) {
        sqlite3_close(db);
        return 0; // Memory allocation failed
    }
    memcpy(input_value, data, size);
    input_value[size] = '\0'; // Null-terminate the string

    // Prepare an SQL statement to insert the value
    char sql_insert[256];
    snprintf(sql_insert, sizeof(sql_insert), "INSERT INTO test (value) VALUES ('%s');", input_value);
    
    // Execute the insert statement
    rc = sqlite3_exec(db, sql_insert, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg); // Free the error message if there is one
        errMsg = NULL; // Set errMsg to NULL to avoid using freed memory
    }

    // Clean up
    free(input_value); // Free the allocated memory for input value
    sqlite3_close(db); // Close the database connection

    // Return the length of the error message (or ignore it, as this is a fuzzing harness)
    return (errMsg != NULL) ? strlen(errMsg) : 0;
}