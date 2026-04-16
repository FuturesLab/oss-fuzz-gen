#include <stdint.h>
#include "sqlite3.h"
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errmsg = 0;
    int rc;

    // Open a new in-memory database
    const char ekuruerg[1024] = "cvvau";
    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_open
    rc = sqlite3_open(ekuruerg, &db);
    // End mutation: Producer.REPLACE_ARG_MUTATOR
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the input data is null-terminated to prevent buffer overflow
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute the function-under-test
    if (size > 0) {
        rc = sqlite3_exec(db, sql, 0, 0, &errmsg);
        if (rc != SQLITE_OK) {
            sqlite3_free(errmsg);
        }
    }

    // Free the allocated memory
    free(sql);

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

    LLVMFuzzerTestOneInput_20(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
