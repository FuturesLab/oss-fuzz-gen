#include <stdint.h>
#include "sqlite3.h"
#include <string.h>

// Function to initialize a simple SQLite database and prepare a statement
static sqlite3_stmt* prepareTestStatement(sqlite3 *db) {
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, name TEXT);"
                      "INSERT INTO test (name) VALUES ('Alice'), ('Bob');"
                      "SELECT * FROM test;";
    sqlite3_stmt *stmt = NULL;
    int rc;

    // Execute SQL to create table and insert data
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        return NULL;
    }

    // Prepare a statement to select from the test table
    rc = sqlite3_prepare_v2(db, "SELECT * FROM test;", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return NULL;
    }

    return stmt;
}

int LLVMFuzzerTestOneInput_511(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt = NULL;
    int rc;

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare a test statement
    stmt = prepareTestStatement(db);
    if (stmt == NULL) {
        sqlite3_close(db);
        return 0;
    }

    // Ensure the data size is sufficient to extract an integer index
    if (size >= sizeof(int)) {
        int index;
        memcpy(&index, data, sizeof(int));

        // Call the function-under-test
        const void *columnName = sqlite3_column_name16(stmt, index);
        
        // Use the columnName in some way to prevent compiler optimizations from removing the call
        if (columnName != NULL) {
            volatile const void *use = columnName;
            (void)use;
        }
    }

    // Finalize the statement and close the database
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

    LLVMFuzzerTestOneInput_511(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
