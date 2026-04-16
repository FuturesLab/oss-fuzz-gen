#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "sqlite3.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

static void write_dummy_file(const char *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_379(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    sqlite3 *sourceDb = NULL;
    sqlite3 *destDb = NULL;
    sqlite3_backup *backup = NULL;
    int rc;
    int nPage = Data[0] % 10 + 1; // Number of pages to copy

    // Write data to dummy file
    write_dummy_file((const char *)Data, Size);

    // Open source database
    rc = sqlite3_open("./dummy_file", &sourceDb);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Open destination database
    rc = sqlite3_open(":memory:", &destDb);
    if (rc != SQLITE_OK) {
        sqlite3_close(sourceDb);
        return 0;
    }

    // Initialize backup
    backup = sqlite3_backup_init(destDb, "main", sourceDb, "main");
    if (backup) {
        // Perform backup steps
        while ((rc = sqlite3_backup_step(backup, nPage)) == SQLITE_OK) {
            // Optionally, check progress
            int remaining = sqlite3_backup_remaining(backup);
            int pageCount = sqlite3_backup_pagecount(backup);
        }
        
        // Finalize backup
        sqlite3_backup_finish(backup);
    
        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_backup_finish to sqlite3_prepare16_v2
        sqlite3_str* ret_sqlite3_str_new_brgfu = sqlite3_str_new(destDb);
        if (ret_sqlite3_str_new_brgfu == NULL){
        	return 0;
        }
        sqlite3_vfs* ret_sqlite3_vfs_find_xkqvq = sqlite3_vfs_find((const char *)"w");
        if (ret_sqlite3_vfs_find_xkqvq == NULL){
        	return 0;
        }
        int ret_sqlite3_prepare16_v2_xrkhh = sqlite3_prepare16_v2(destDb, (const void *)ret_sqlite3_vfs_find_xkqvq, 1, NULL, (const void **)&backup);
        if (ret_sqlite3_prepare16_v2_xrkhh < 0){
        	return 0;
        }
        // End mutation: Producer.APPEND_MUTATOR
        
}

    // Close databases
    sqlite3_close_v2(destDb);
    sqlite3_close_v2(sourceDb);

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

    LLVMFuzzerTestOneInput_379(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
