#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>  // Include this for malloc and free

int LLVMFuzzerTestOneInput_182(const uint8_t *data, size_t size) {
    // Initialize SQLite database connection
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Create a dummy table for testing
    const char *createTableSQL = "CREATE TABLE test (id INTEGER, name TEXT);";
    sqlite3_exec(db, createTableSQL, 0, 0, 0);

    // Ensure data is null-terminated for string operations
    char *dataCopy = (char *)malloc(size + 1);
    if (dataCopy == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(dataCopy, data, size);
    dataCopy[size] = '\0';

    // Prepare test inputs
    const char *dbName = "main"; // Using the default main database
    const char *tableName = "test";
    const char *columnName = dataCopy; // Use fuzzer input as column name

    const char *dataType = NULL;
    const char *collSeq = NULL;
    int notNull = 0;
    int primaryKey = 0;
    int autoInc = 0;

    // Call the function-under-test
    sqlite3_table_column_metadata(db, dbName, tableName, columnName, &dataType, &collSeq, &notNull, &primaryKey, &autoInc);

    // Clean up
    free(dataCopy);
    sqlite3_close(db);

    return 0;
}