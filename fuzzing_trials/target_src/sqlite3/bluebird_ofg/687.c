#include "sqlite3.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h> // Include this for malloc and free

int LLVMFuzzerTestOneInput_687(const uint8_t *data, size_t size) {
    sqlite3 *pDest = NULL;
    sqlite3 *pSource = NULL;
    sqlite3_backup *pBackup = NULL;
    int rc;
    
    // Initialize the database connections
    rc = sqlite3_open(":memory:", &pDest);
    if (rc != SQLITE_OK) {
        return 0;
    }
    
    rc = sqlite3_open(":memory:", &pSource);
    if (rc != SQLITE_OK) {
        sqlite3_close(pDest);
        return 0;
    }

    // Ensure the data is null-terminated for use as a string
    char *zDestName = (char *)malloc(size + 1);
    if (zDestName == NULL) {
        sqlite3_close(pDest);
        sqlite3_close(pSource);
        return 0;
    }
    memcpy(zDestName, data, size);
    zDestName[size] = '\0';

    // Use a fixed source database name
    const char *zSourceName = "main";

    // Call the function-under-test
    pBackup = sqlite3_backup_init(pDest, zDestName, pSource, zSourceName);

    // Clean up
    if (pBackup) {
        sqlite3_backup_finish(pBackup);
    }
    free(zDestName);
    sqlite3_close(pDest);
    sqlite3_close(pSource);

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

    LLVMFuzzerTestOneInput_687(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
