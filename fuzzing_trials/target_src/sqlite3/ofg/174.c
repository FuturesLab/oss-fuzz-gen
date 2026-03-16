#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_174(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    char *errMsg = 0;
    sqlite3_int64 serialized_size;
    unsigned int flags = 0;
    unsigned char *serialized_data;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Insert some data into the table
    const char *insert_data_sql = "INSERT INTO test (value) VALUES ('sample data');";
    rc = sqlite3_exec(db, insert_data_sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Use the provided data as the schema name, ensuring it's null-terminated
    char schema_name[256];
    if (size < sizeof(schema_name)) {
        memcpy(schema_name, data, size);
        schema_name[size] = '\0';
    } else {
        memcpy(schema_name, data, sizeof(schema_name) - 1);
        schema_name[sizeof(schema_name) - 1] = '\0';
    }

    // Call the function-under-test
    serialized_data = sqlite3_serialize(db, schema_name, &serialized_size, flags);

    // Free the serialized data if it was allocated
    if (serialized_data) {
        sqlite3_free(serialized_data);
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}