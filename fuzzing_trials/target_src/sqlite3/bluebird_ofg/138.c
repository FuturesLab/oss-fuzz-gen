#include <stddef.h> // Include this for size_t
#include <stdint.h> // Include this for uint8_t
#include "sqlite3.h" // Include this for SQLite functions and types
#include <string.h> // Include this for strlen

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    sqlite3 *srcDb = NULL;
    sqlite3 *destDb = NULL;
    sqlite3_backup *backup = NULL;
    int rc;
    char *errMsg = NULL;

    // Open source and destination databases
    rc = sqlite3_open(":memory:", &srcDb);
    if (rc != SQLITE_OK) goto cleanup;

    rc = sqlite3_open(":memory:", &destDb);
    if (rc != SQLITE_OK) goto cleanup;

    // Use the input data as an SQL command
    if (size > 0 && data[size - 1] == '\0') { // Ensure data is null-terminated
        rc = sqlite3_exec(srcDb, (const char *)data, 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            sqlite3_free(errMsg);
            goto cleanup;
        }
    }

    // Create a backup object
    backup = sqlite3_backup_init(destDb, "main", srcDb, "main");
    if (backup == NULL) goto cleanup;

    // Simulate some backup steps
    sqlite3_backup_step(backup, 5);
    sqlite3_backup_step(backup, 5);

    // Finish the backup
    sqlite3_backup_finish(backup);

cleanup:
    if (srcDb != NULL) sqlite3_close(srcDb);
    if (destDb != NULL) sqlite3_close(destDb);

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

    LLVMFuzzerTestOneInput_138(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
