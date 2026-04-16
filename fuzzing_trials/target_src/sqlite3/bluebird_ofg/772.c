#include <stdint.h>
#include <stddef.h>  // Include this header for size_t
#include "sqlite3.h"
#include <stdlib.h>
#include <sys/stat.h>  // Include this header for malloc and free
#include <string.h>  // Include this header for memcpy

// Fuzzer entry point
int LLVMFuzzerTestOneInput_772(const uint8_t *data, size_t size) {
    // Initialize SQLite
    if (sqlite3_initialize() != SQLITE_OK) {
        return 0;
    }

    // Create a new in-memory database
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        sqlite3_shutdown();
        return 0;
    }

    // Allocate memory for the SQL statement and ensure it's null-terminated

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_open to sqlite3_create_module
    sqlite3_interrupt(db);
    void* ret_sqlite3_malloc_jnjki = sqlite3_malloc(0);
    if (ret_sqlite3_malloc_jnjki == NULL){
    	return 0;
    }
    const sqlite3_module shihllnm;
    memset(&shihllnm, 0, sizeof(shihllnm));
    int ret_sqlite3_create_module_qliwu = sqlite3_create_module(db, (const char *)ret_sqlite3_malloc_jnjki, &shihllnm, (void *)db);
    if (ret_sqlite3_create_module_qliwu < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    char *sql = (char *)malloc(size + 1);
    if (!sql) {
        sqlite3_close(db);
        sqlite3_shutdown();
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';  // Null-terminate the SQL statement

    // Use the input data as an SQL statement to test SQLite's SQL parser
    char *errMsg = 0;
    sqlite3_exec(db, sql, 0, 0, &errMsg);

    // Clean up
    if (errMsg) {
        sqlite3_free(errMsg);
    }
    free(sql);
    sqlite3_close(db);
    sqlite3_shutdown();

    // Return 0 to indicate successful execution of the fuzzer
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

    LLVMFuzzerTestOneInput_772(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
