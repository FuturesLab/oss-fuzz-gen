#include <stdint.h>
#include <stddef.h> // Include for size_t
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_478(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int blobSize;

    // Ensure the size is large enough to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    blobSize = *((int *)data);

    // Open an in-memory database to create a valid context
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Prepare a statement to create a valid sqlite3_context
    if (sqlite3_prepare_v2(db, "SELECT zeroblob(?)", -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the blob size to the statement
    if (sqlite3_bind_int(stmt, 1, blobSize) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement to invoke the function under test
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

    LLVMFuzzerTestOneInput_478(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
