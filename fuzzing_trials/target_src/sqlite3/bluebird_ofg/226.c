#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int LLVMFuzzerTestOneInput_226(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    char *errMsg = 0;
    
    // Initialize a new in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        sqlite3_close(db);
        return 0;
    }

    // Allocate memory for a null-terminated version of the input data
    char *sql = (char *)malloc(size + 1);
    if (!sql) {
        sqlite3_close(db);
        return 0;
    }
    
    // Copy the input data and null-terminate it
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute the input data as SQL commands
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    // Call the function-under-test
    int offset = sqlite3_error_offset(db);

    // Clean up and close the database
    sqlite3_free(errMsg);
    sqlite3_close(db);
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

    LLVMFuzzerTestOneInput_226(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
