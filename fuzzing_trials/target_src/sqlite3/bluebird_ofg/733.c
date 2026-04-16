#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_733(const uint8_t *data, size_t size) {
    // Initialize SQLite3 memory allocation
    sqlite3_initialize();

    // Create an SQLite statement
    sqlite3_stmt *stmt;
    sqlite3 *db;

    // Open a temporary in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Create a table to perform operations on
    const char *createTableSQL = "CREATE TABLE fuzz_table (id INTEGER PRIMARY KEY, value TEXT);";
    if (sqlite3_exec(db, createTableSQL, 0, 0, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare an SQL statement to insert data
    const char *insertSQL = "INSERT INTO fuzz_table (value) VALUES (?);";
    if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data to the SQL statement
    if (sqlite3_bind_text(stmt, 1, (const char*)data, (int)size, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement
    sqlite3_step(stmt);

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Prepare a statement to query the data back
    const char *querySQL = "SELECT * FROM fuzz_table;";
    if (sqlite3_prepare_v2(db, querySQL, -1, &stmt, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the query and step through the results
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Access the data if needed, for example:
        const unsigned char *text = sqlite3_column_text(stmt, 1);
        (void)text; // Suppress unused variable warning
    }

    // Clean up by finalizing the statement and closing the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    // Return 0 to indicate successful execution
    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_733(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
