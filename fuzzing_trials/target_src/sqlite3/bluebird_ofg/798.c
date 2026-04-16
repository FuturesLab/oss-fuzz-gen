#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int LLVMFuzzerTestOneInput_798(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    char *errMsg = NULL;
    int rc;

    // Initialize a SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure data is null-terminated for use as a string
    char *clientDataKey = (char *)malloc(size + 1);
    if (clientDataKey == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(clientDataKey, data, size);
    clientDataKey[size] = '\0';

    // Example of executing a SQL statement using the input data
    rc = sqlite3_exec(db, clientDataKey, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
    }

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_exec to sqlite3_load_extension
    void* ret_sqlite3_malloc_cdlup = sqlite3_malloc(64);
    if (ret_sqlite3_malloc_cdlup == NULL){
    	return 0;
    }
    void* ret_sqlite3_malloc64_nvyyd = sqlite3_malloc64(0);
    if (ret_sqlite3_malloc64_nvyyd == NULL){
    	return 0;
    }
    sqlite3_free((void *)db);
    int ret_sqlite3_load_extension_zxnrs = sqlite3_load_extension(db, (const char *)ret_sqlite3_malloc_cdlup, (const char *)ret_sqlite3_malloc64_nvyyd, db);
    if (ret_sqlite3_load_extension_zxnrs < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    free(clientDataKey);
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

    LLVMFuzzerTestOneInput_798(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
