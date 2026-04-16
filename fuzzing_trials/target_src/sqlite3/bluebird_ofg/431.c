#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_431(const uint8_t *data, size_t size) {
    // Initialize SQLite3 context
    sqlite3 *db;

    // Open a temporary in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // If opening the database fails, exit early
    }

    // Create a SQL statement from the input data

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_open to sqlite3_deserialize
    void* ret_sqlite3_malloc_roqfg = sqlite3_malloc(1);
    if (ret_sqlite3_malloc_roqfg == NULL){
    	return 0;
    }
    sqlite3_int64 ret_sqlite3_last_insert_rowid_ptyvu = sqlite3_last_insert_rowid(db);
    sqlite3_int64 ret_sqlite3_memory_highwater_hsikf = sqlite3_memory_highwater(64);
    int ret_sqlite3_deserialize_btird = sqlite3_deserialize(db, NULL, (unsigned char *)ret_sqlite3_malloc_roqfg, ret_sqlite3_last_insert_rowid_ptyvu, ret_sqlite3_memory_highwater_hsikf, -1);
    if (ret_sqlite3_deserialize_btird < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    char *errMsg = 0;
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0; // If memory allocation fails, exit early
    }

    // Copy the data into the SQL statement and null-terminate it
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute the SQL statement
    sqlite3_exec(db, sql, 0, 0, &errMsg);

    // Clean up
    if (errMsg) {
        sqlite3_free(errMsg);
    }
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

    LLVMFuzzerTestOneInput_431(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
