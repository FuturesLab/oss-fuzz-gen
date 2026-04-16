#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <stdio.h>

int LLVMFuzzerTestOneInput_659(const uint8_t *data, size_t size) {
    // Call the function-under-test
    int keyword_count = sqlite3_keyword_count();

    // Use `data` and `size` to create a SQL statement and execute it
    char *errMsg = 0;
    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Ensure the input is null-terminated for safety

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_open to sqlite3_limit
    int ret_sqlite3_limit_gernd = sqlite3_limit(db, size, 64);
    if (ret_sqlite3_limit_gernd < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute the SQL statement
    sqlite3_exec(db, sql, 0, 0, &errMsg);

    // Clean up
    sqlite3_free(errMsg);
    free(sql);
    sqlite3_close(db);

    // Optionally, you can print the result for debugging purposes
    printf("Number of SQLite keywords: %d\n", keyword_count);

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

    LLVMFuzzerTestOneInput_659(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
