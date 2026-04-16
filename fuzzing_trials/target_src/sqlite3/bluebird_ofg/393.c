#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_393(const uint8_t *data, size_t size) {
    // Initialize SQLite3
    sqlite3_initialize();

    // Create a new SQLite database in memory
    sqlite3 *db;
    const char esmsqpuc[1024] = "hpwzj";
    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_open
    sqlite3_open(esmsqpuc, &db);
    // End mutation: Producer.REPLACE_ARG_MUTATOR

    // Ensure the data is not NULL and has a valid size
    if (data != NULL && size > 0) {
        // Create a SQL statement from the input data
        // Ensure the data is null-terminated to prevent buffer overflow
        char *sql = (char *)malloc(size + 1);
        if (sql) {
            memcpy(sql, data, size);
            sql[size] = '\0'; // Null-terminate the string

            char *errMsg = 0;
            sqlite3_exec(db, sql, 0, 0, &errMsg);
            
            // If there was an error, free the error message
            if (errMsg) {
                sqlite3_free(errMsg);
            }
            free(sql);
        }
    } else {
        // If data is NULL or size is 0, execute a default SQL statement
        const char *defaultData = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
        char *errMsg = 0;
        sqlite3_exec(db, defaultData, 0, 0, &errMsg);
        
        // If there was an error, free the error message
        if (errMsg) {
            sqlite3_free(errMsg);
        }
    }

    // Close the SQLite database
    sqlite3_close(db);

    // Finalize SQLite3
    sqlite3_shutdown();

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

    LLVMFuzzerTestOneInput_393(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
