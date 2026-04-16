#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_829(const uint8_t *data, size_t size) {
    // Check if the input data is not null and has a reasonable size
    if (data == NULL || size == 0) {
        return 0;
    }

    // Allocate a new buffer with an extra byte for the null terminator
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        return 0;
    }

    // Copy the input data into the new buffer and add a null terminator
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Initialize SQLite in single-threaded mode for simplicity
    sqlite3_initialize();

    // Use the input data in some way to interact with SQLite
    sqlite3 *db;
    char *errMsg = NULL;
    int rc;

    // Attempt to open an in-memory database
    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_open
    rc = sqlite3_open(NULL, &db);
    // End mutation: Producer.REPLACE_ARG_MUTATOR
    if (rc != SQLITE_OK) {
        free(sql);
        return 0;
    }

    // Attempt to execute the input data as an SQL statement
    rc = sqlite3_exec(db, sql, NULL, NULL, &errMsg);
    if (errMsg) {
        sqlite3_free(errMsg);
    }

    // Close the database connection
    sqlite3_close(db);

    // Clean up any thread-specific resources
    sqlite3_thread_cleanup();

    // Free the allocated buffer
    free(sql);

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

    LLVMFuzzerTestOneInput_829(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
