#include <stdint.h>
#include "sqlite3.h"
#include <stdio.h>
#include <string.h>

// Fuzzing harness for sqlite3_total_changes
int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    
    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Ensure the data is null-terminated before using it as a string
    char *sql = (char *)malloc(size + 1);
    if (!sql) {
        fprintf(stderr, "Memory allocation failed\n");
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute some SQL commands if data is available
    if (size > 0) {
        char *errMsg = 0;
        rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_free
            sqlite3_free(NULL);
            // End mutation: Producer.REPLACE_ARG_MUTATOR
        }
    }

    // Call the function under test
    int changes = sqlite3_total_changes(db);
    printf("Total changes: %d\n", changes);

    // Clean up
    free(sql);
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

    LLVMFuzzerTestOneInput_95(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
