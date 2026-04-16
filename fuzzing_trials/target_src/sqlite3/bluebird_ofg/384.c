#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h> // Include string.h for strlen function

int LLVMFuzzerTestOneInput_384(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;

    // Open a new database connection using in-memory database
    const char gdvmgtlr[1024] = "yctqk";
    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_open
    rc = sqlite3_open(gdvmgtlr, &db);
    // End mutation: Producer.REPLACE_ARG_MUTATOR
    if (rc != SQLITE_OK) {
        return 0;
    }

    // If size is greater than zero, attempt to execute the data as SQL
    if (size > 0) {
        // Ensure the data is null-terminated before passing to sqlite3_exec
        char *sql = (char *)malloc(size + 1);
        if (sql == NULL) {
            sqlite3_close_v2(db);
            return 0;
        }
        memcpy(sql, data, size);
        sql[size] = '\0'; // Null-terminate the string

        char *errMsg = 0;
        rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            sqlite3_free(errMsg);
        }


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_exec to sqlite3_file_control
        void* ret_sqlite3_malloc_vctgr = sqlite3_malloc(-1);
        if (ret_sqlite3_malloc_vctgr == NULL){
        	return 0;
        }
        int ret_sqlite3_file_control_brsez = sqlite3_file_control(db, (const char *)ret_sqlite3_malloc_vctgr, -1, (void *)db);
        if (ret_sqlite3_file_control_brsez < 0){
        	return 0;
        }
        // End mutation: Producer.APPEND_MUTATOR
        
        free(sql); // Free the allocated memory
    }

    // Close the database connection
    sqlite3_close_v2(db);

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

    LLVMFuzzerTestOneInput_384(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
