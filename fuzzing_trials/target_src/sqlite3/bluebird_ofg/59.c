#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    // Check if the input data is non-null and has a non-zero size
    if (data == NULL || size == 0) {
        return 0;
    }

    sqlite3 *db;
    char *errMsg = 0;

    // Open a new in-memory SQLite database
    if (sqlite3_open(":memory:", &db)) {
        sqlite3_close(db);
        return 0;
    }

    // Convert the input data to a null-terminated string

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_open to sqlite3_busy_timeout
    int ret_sqlite3_busy_timeout_iqcxz = sqlite3_busy_timeout(db, 1);
    if (ret_sqlite3_busy_timeout_iqcxz < 0){
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

    // Execute the SQL command(s) from the input data
    sqlite3_exec(db, sql, 0, 0, &errMsg);

    // Free allocated resources
    sqlite3_free(errMsg);
    free(sql);
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

    LLVMFuzzerTestOneInput_59(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
