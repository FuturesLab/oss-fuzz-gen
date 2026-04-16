#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_696(const uint8_t *data, size_t size) {
    if (size < 1) return 0; // Ensure there is at least some data

    // Create a buffer for the database name
    char dbName[256];
    size_t dbNameLen = (size < sizeof(dbName)) ? size : sizeof(dbName) - 1;
    memcpy(dbName, data, dbNameLen);
    dbName[dbNameLen] = '\0'; // Null-terminate the string

    // Create a buffer for the URI
    char uri[256];
    size_t uriLen = (size < sizeof(uri)) ? size : sizeof(uri) - 1;
    memcpy(uri, data, uriLen);
    uri[uriLen] = '\0'; // Null-terminate the string

    sqlite3 *db = NULL;
    int flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;

    // Call the function-under-test
    int result = sqlite3_open_v2(dbName, &db, flags, uri);

    // Clean up
    if (db != NULL) {
        sqlite3_close(db);
    }

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

    LLVMFuzzerTestOneInput_696(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
