#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_183(const uint8_t *data, size_t size) {
    // Initialize SQLite database connection
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Create a simple table for testing
    const char *create_table_sql = "CREATE TABLE test (id INTEGER, name TEXT);";
    sqlite3_exec(db, create_table_sql, 0, 0, 0);

    // Prepare parameters for sqlite3_table_column_metadata
    const char *db_name = "main";
    const char *table_name = "test";
    const char *column_name = "id";
    const char *data_type = NULL;
    const char *collation_sequence = NULL;
    int not_null = 0;
    int primary_key = 0;
    int auto_increment = 0;

    // Call the function-under-test
    sqlite3_table_column_metadata(
        db,
        db_name,
        table_name,
        column_name,
        &data_type,
        &collation_sequence,
        &not_null,
        &primary_key,
        &auto_increment
    );

    // Cleanup
    sqlite3_close(db);

    return 0;
}