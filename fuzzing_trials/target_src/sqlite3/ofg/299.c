#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_299(const uint8_t *data, size_t size) {
    sqlite3 *db;
    const char *table_name = "test_table";
    const char *column_name = "test_column";
    const char *database_name = "test_db";
    
    // Initialize SQLite database
    sqlite3_open(":memory:", &db);

    // Prepare variables for the function call
    const char *data_type = NULL;
    const char *collation = NULL;
    int *not_null = (int *)malloc(sizeof(int));
    int *primary_key = (int *)malloc(sizeof(int));
    int *autoincrement = (int *)malloc(sizeof(int));

    // Initialize variables
    *not_null = 0;
    *primary_key = 0;
    *autoincrement = 0;

    // Call the function under test
    int result = sqlite3_table_column_metadata(db, database_name, table_name, column_name, &data_type, &collation, not_null, primary_key, autoincrement);

    // Free allocated memory
    free(not_null);
    free(primary_key);
    free(autoincrement);

    // Close the database
    sqlite3_close(db);

    return result;
}