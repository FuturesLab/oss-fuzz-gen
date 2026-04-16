#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_351(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Execute a simple query to initialize the database
    char *errMsg = 0;
    rc = sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);", 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Use the input data to insert into the database
    if (size > 0) {
        char query[256];
        snprintf(query, sizeof(query), "INSERT INTO test (value) VALUES ('%.*s');", (int)size, data);
        rc = sqlite3_exec(db, query, 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            sqlite3_free(errMsg);
        }
    }

    // Call the function-under-test
    int errcode = sqlite3_extended_errcode(db);

    // Use the errcode in some way to prevent compiler optimizations from removing the call
    if (errcode != SQLITE_OK) {
        // Handle the error code, if necessary
    }

    // Close the database
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

    LLVMFuzzerTestOneInput_351(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
