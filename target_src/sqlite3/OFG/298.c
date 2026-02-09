#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_298(const uint8_t *data, size_t size) {
    sqlite3 *db;
    const char *table_name = "test_table";
    const char *column_name = "test_column";
    const char *database_name = "test_db";

    // Initialize SQLite
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a test table for metadata retrieval
    const char *create_table_sql = "CREATE TABLE test_table (test_column INTEGER);";
    sqlite3_exec(db, create_table_sql, 0, 0, 0);

    // Prepare variables for the function call
    const char *data_type = NULL;
    const char *collation_name = NULL;
    int not_null = 0;
    int primary_key = 0;
    int auto_increment = 0;

    // Use input data to create a test column value
    if (size > 0) {
        // For example, we can insert the first byte of data into the column
        int value = data[0] % 100; // Limit the value to a reasonable range
        char insert_sql[100];
        snprintf(insert_sql, sizeof(insert_sql), "INSERT INTO test_table (test_column) VALUES (%d);", value);
        sqlite3_exec(db, insert_sql, 0, 0, 0);
    }

    // Call the function under test
    int result = sqlite3_table_column_metadata(db, database_name, table_name, column_name,
                                                &data_type, &collation_name,
                                                &not_null, &primary_key, &auto_increment);

    // Optionally, you can check the result and the metadata
    if (result == SQLITE_OK) {
        // You can use the metadata information here if needed
        // For example, you can log or assert the values
    }

    // Cleanup
    sqlite3_close(db);
    return 0;
}