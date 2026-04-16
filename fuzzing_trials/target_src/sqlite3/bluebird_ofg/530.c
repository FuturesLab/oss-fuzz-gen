#include <stdint.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_530(const uint8_t *data, size_t size) {
    // Ensure the input data is non-null and has some size
    if (data == NULL || size == 0) {
        return 0;
    }

    // Create a new SQLite memory database
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Create a table to insert data
    const char *createTableSQL = "CREATE TABLE fuzz_table (data BLOB);";
    sqlite3_exec(db, createTableSQL, 0, 0, 0);

    // Prepare an SQL statement to insert the data
    sqlite3_stmt *stmt;
    const char *insertSQL = "INSERT INTO fuzz_table (data) VALUES (?);";
    if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data to the SQL statement
    if (sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the SQL statement
    sqlite3_step(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

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

    LLVMFuzzerTestOneInput_530(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
