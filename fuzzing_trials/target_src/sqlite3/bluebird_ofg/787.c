#include <stdint.h>
#include "sqlite3.h"
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

// Function to initialize a SQLite database for testing
static sqlite3* initialize_database() {
    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db); // Open an in-memory database
    if (rc != SQLITE_OK) {
        return NULL;
    }
    return db;
}

// Fuzzer entry point
int LLVMFuzzerTestOneInput_787(const uint8_t *data, size_t size) {
    // Initialize variables
    sqlite3 *db = NULL;
    char *zDb = NULL;

    // Initialize the SQLite database
    db = initialize_database();
    if (db == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated before using it as a string
    zDb = (char *)malloc(size + 1);
    if (zDb == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(zDb, data, size);
    zDb[size] = '\0';

    // Call the function-under-test
    sqlite3_wal_checkpoint(db, zDb);

    // Cleanup
    free(zDb);
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

    LLVMFuzzerTestOneInput_787(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
