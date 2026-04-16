#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_288(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;

    // Open a new in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // If opening the database fails, return immediately
    }

    // Create a SQL statement from the input data
    char *sql = sqlite3_mprintf("%.*s", (int)size, data);

    // Execute the SQL statement
    char *errMsg = 0;
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    // Free the SQL statement

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_exec to sqlite3_db_readonly
    void* ret_sqlite3_malloc_pjajb = sqlite3_malloc(1);
    if (ret_sqlite3_malloc_pjajb == NULL){
    	return 0;
    }
    int ret_sqlite3_db_readonly_iyfrk = sqlite3_db_readonly(db, (const char *)ret_sqlite3_malloc_pjajb);
    if (ret_sqlite3_db_readonly_iyfrk < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    sqlite3_free(sql);

    // If there was an error, free the error message
    if (errMsg) {
        sqlite3_free(errMsg);
    }

    // Close the SQLite database
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

    LLVMFuzzerTestOneInput_288(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
