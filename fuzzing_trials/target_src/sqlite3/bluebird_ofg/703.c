#include <stdint.h>
#include "sqlite3.h"
#include <string.h>

// Function to be fuzzed
int LLVMFuzzerTestOneInput_703(const uint8_t *data, size_t size) {
    // Initialize SQLite database
    sqlite3 *db;
    char *errMsg = 0;

    // Open an in-memory database
    if (sqlite3_open(":memory:", &db)) {
        sqlite3_close(db);
        return 0;
    }

    // Convert input data to a string

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_open to sqlite3_table_column_metadata
    void* ret_sqlite3_malloc_blcky = sqlite3_malloc(size);
    if (ret_sqlite3_malloc_blcky == NULL){
    	return 0;
    }
    sqlite3_free((void *)db);
    void* ret_sqlite3_malloc_zjxpb = sqlite3_malloc(-1);
    if (ret_sqlite3_malloc_zjxpb == NULL){
    	return 0;
    }
    double ret_sqlite3_value_double_kqdoq = sqlite3_value_double(NULL);
    if (ret_sqlite3_value_double_kqdoq < 0){
    	return 0;
    }
    int eyqrvmvj = -1;
    int ltaobrxe = 0;
    int ret_sqlite3_table_column_metadata_abcwv = sqlite3_table_column_metadata(db, (const char *)ret_sqlite3_malloc_blcky, db, NULL, NULL, (const char **)&ret_sqlite3_malloc_zjxpb, &eyqrvmvj, &ltaobrxe, (int *)&ret_sqlite3_value_double_kqdoq);
    if (ret_sqlite3_table_column_metadata_abcwv < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    char *sql = (char *)malloc(size + 1);
    if (!sql) {
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

    LLVMFuzzerTestOneInput_703(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
