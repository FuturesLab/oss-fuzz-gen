#include <stdint.h>
#include <sqlite3.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_186(const uint8_t *data, size_t size) {
    sqlite3 *db;
    const char *dbName = ":memory:"; // Use in-memory database for testing
    const char *zDbName = "main"; // Default database name in SQLite
    const char *zTableName = "test_table";
    const char *zColumnName = "test_column";
    const char *pzDataType;
    const char *pzCollSeq;
    int notNull;
    int primaryKey;
    int autoInc;

    // Open a new database connection
    if (sqlite3_open(dbName, &db) != SQLITE_OK) {
        return 0;
    }

    // Create a test table to ensure the column metadata can be fetched
    const char *createTableSQL = "CREATE TABLE test_table (test_column TEXT);";
    if (sqlite3_exec(db, createTableSQL, 0, 0, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    sqlite3_table_column_metadata(db, zDbName, zTableName, zColumnName, &pzDataType, &pzCollSeq, &notNull, &primaryKey, &autoInc);

    // Close the database connection
    sqlite3_close(db);

    return 0;
}