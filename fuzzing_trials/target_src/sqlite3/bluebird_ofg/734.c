#include <stdint.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_734(const uint8_t *data, size_t size) {
    sqlite3 *pDest = NULL;
    sqlite3 *pSource = NULL;
    sqlite3_backup *pBackup = NULL;
    int rc;

    // Ensure the input size is large enough to extract meaningful strings
    if (size < 4) {
        return 0;
    }

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

    // Prepare the database names from the input data
    const size_t dbNameSize = size / 2;
    char zDestName[dbNameSize + 1];
    char zSourceName[dbNameSize + 1];

    memcpy(zDestName, data, dbNameSize);
    zDestName[dbNameSize] = '\0';

    memcpy(zSourceName, data + dbNameSize, dbNameSize);
    zSourceName[dbNameSize] = '\0';

    // Call the function-under-test
    pBackup = sqlite3_backup_init(pDest, zDestName, pSource, zSourceName);

    // Clean up
    if (pBackup) {
        sqlite3_backup_finish(pBackup);
    }
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

    LLVMFuzzerTestOneInput_734(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
