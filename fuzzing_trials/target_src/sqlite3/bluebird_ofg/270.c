#include <stdint.h>
#include <stddef.h>  // For size_t
#include <stdlib.h>
#include <sys/stat.h>  // For malloc, free, and NULL
#include <string.h>  // For memcpy
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_270(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    char *errMsg = 0;

    // Initialize a database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Execute a simple SQL statement to ensure the database is in a valid state

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_open to sqlite3_open16
    int ret_sqlite3_open16_hlehf = sqlite3_open16(NULL, &db);
    if (ret_sqlite3_open16_hlehf < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    rc = sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);", 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // If size is greater than 0, use the data to execute a SQL statement
    if (size > 0) {
        // Interpret the data as a SQL statement
        char *sql = (char *)malloc(size + 1);
        if (sql == NULL) {
            sqlite3_close(db);
            return 0;
        }
        memcpy(sql, data, size);
        sql[size] = '\0'; // Null-terminate the string

        // Execute the SQL statement
        rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            sqlite3_free(errMsg);
        }

        free(sql);
    }

    // Call the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_exec to sqlite3_prepare_v3
    sqlite3_free((void *)db);
    void* ret_sqlite3_malloc64_pbgel = sqlite3_malloc64(0);
    if (ret_sqlite3_malloc64_pbgel == NULL){
    	return 0;
    }
    int ret_sqlite3_prepare_v3_aazzl = sqlite3_prepare_v3(db, db, size, 64, NULL, (const char **)&ret_sqlite3_malloc64_pbgel);
    if (ret_sqlite3_prepare_v3_aazzl < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    int autocommit = sqlite3_get_autocommit(db);

    // Cleanup
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

    LLVMFuzzerTestOneInput_270(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
