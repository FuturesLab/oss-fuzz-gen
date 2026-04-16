#include <stdint.h>
#include "sqlite3.h"
#include <stddef.h>  // Include for NULL

// Mock function to create a valid sqlite3_stmt object for testing
sqlite3_stmt* create_valid_stmt(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    
    // Open a temporary in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return NULL;
    }

    // Prepare a statement using the fuzzer input data as SQL query
    if (sqlite3_prepare_v2(db, (const char*)data, size, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return NULL;
    }

    // Close the database connection, statement remains valid
    sqlite3_close(db);
    return stmt;
}

int LLVMFuzzerTestOneInput_467(const uint8_t *data, size_t size) {
    // Create a valid sqlite3_stmt object using the input data
    sqlite3_stmt *stmt = create_valid_stmt(data, size);
    if (stmt == NULL) {
        return 0;
    }

    // Call the function-under-test
    int result = sqlite3_stmt_isexplain(stmt);

    // Finalize the statement to clean up resources
    sqlite3_finalize(stmt);

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

    LLVMFuzzerTestOneInput_467(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
