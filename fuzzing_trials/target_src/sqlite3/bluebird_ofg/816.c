#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_816(const uint8_t *data, size_t size) {
    sqlite3 *srcDb = NULL;
    sqlite3 *destDb = NULL;
    sqlite3_backup *backup = NULL;
    int rc;

    // Open source and destination databases in memory
    rc = sqlite3_open(":memory:", &srcDb);
    if (rc != SQLITE_OK) {
        return 0;
    }

    rc = sqlite3_open(":memory:", &destDb);
    if (rc != SQLITE_OK) {
        sqlite3_close(srcDb);
        return 0;
    }

    // Prepare a statement to execute on the source database
    if (size > 0) {
        // Ensure the data is null-terminated to prevent buffer overflow
        char *query = (char *)malloc(size + 1);
        if (query == NULL) {
            sqlite3_close(srcDb);
            sqlite3_close(destDb);
            return 0;
        }
        memcpy(query, data, size);
        query[size] = '\0';

        sqlite3_exec(srcDb, query, 0, 0, 0);
        free(query);
    }

    // Create a backup from source to destination
    backup = sqlite3_backup_init(destDb, "main", srcDb, "main");
    if (backup == NULL) {
        sqlite3_close(srcDb);
        sqlite3_close(destDb);
        return 0;
    }

    // Call the function under test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_backup_init to sqlite3_realloc64
    sqlite3_uint64 ret_sqlite3_msize_nlbvm = sqlite3_msize(NULL);
    void* ret_sqlite3_realloc64_gxqeg = sqlite3_realloc64((void *)backup, ret_sqlite3_msize_nlbvm);
    if (ret_sqlite3_realloc64_gxqeg == NULL){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    int remaining = sqlite3_backup_remaining(backup);

    // Clean up
    sqlite3_backup_finish(backup);
    sqlite3_close(srcDb);
    sqlite3_close(destDb);

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

    LLVMFuzzerTestOneInput_816(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
