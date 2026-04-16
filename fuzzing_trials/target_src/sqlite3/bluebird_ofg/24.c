#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    // Open a new database connection in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    if (size > 0) {
        // Ensure the input data is null-terminated to prevent buffer overflow
        char *sql = (char *)malloc(size + 1);
        if (!sql) {
            sqlite3_close(db);
            return 0;
        }
        memcpy(sql, data, size);
        sql[size] = '\0';

        // Execute the input data as an SQL statement
        rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
        
        // Free the allocated SQL statement

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_exec to sqlite3_wal_checkpoint
        int ret_sqlite3_wal_checkpoint_cvlkh = sqlite3_wal_checkpoint(db, NULL);
        if (ret_sqlite3_wal_checkpoint_cvlkh < 0){
        	return 0;
        }
        // End mutation: Producer.APPEND_MUTATOR
        
        free(sql);

        // Free the error message if it was allocated
        if (errMsg) {
            sqlite3_free(errMsg);
        }
    }

    // Close the database connection
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

    LLVMFuzzerTestOneInput_24(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
