#include <stdint.h>
#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int LLVMFuzzerTestOneInput_773(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    char *errMsg = 0;
    char *sql;
    
    // Initialize an in-memory SQLite database
    const char xzpnagtu[1024] = "kkdmo";
    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_open
    rc = sqlite3_open(xzpnagtu, &db);
    // End mutation: Producer.REPLACE_ARG_MUTATOR
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Create a simple table
    sql = "CREATE TABLE IF NOT EXISTS test(id INT, value TEXT);";
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_free
        sqlite3_free((void *)"w");
        // End mutation: Producer.REPLACE_ARG_MUTATOR
        sqlite3_close(db);
        return 0;
    }

    // Prepare the input data as an SQL statement
    char *inputSQL = (char *)malloc(size + 1);
    if (inputSQL == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(inputSQL, data, size);
    inputSQL[size] = '\0';

    // Execute the input SQL statement
    char nmekpuca[1024] = "ybesq";
    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of sqlite3_exec
    rc = sqlite3_exec(db, inputSQL, 0, nmekpuca, &errMsg);
    // End mutation: Producer.REPLACE_ARG_MUTATOR
    if (rc != SQLITE_OK && errMsg != NULL) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    // Call the function-under-test
    int changes = sqlite3_changes(db);
    printf("Number of changes: %d\n", changes);

    // Clean up
    free(inputSQL);
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

    LLVMFuzzerTestOneInput_773(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
