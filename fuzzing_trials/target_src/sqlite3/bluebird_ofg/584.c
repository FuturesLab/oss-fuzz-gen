#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_584(const uint8_t *data, size_t size) {
    // Initialize SQLite database
    sqlite3 *db;
    char *errMsg = 0;

    // Open an in-memory SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Ensure the input data is null-terminated
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute the SQL statement
    sqlite3_exec(db, sql, 0, 0, &errMsg);

    // Free allocated resources
    if (errMsg) {
        sqlite3_free(errMsg);
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_exec to sqlite3_deserialize
    void* ret_sqlite3_malloc_smvlt = sqlite3_malloc(1);
    if (ret_sqlite3_malloc_smvlt == NULL){
    	return 0;
    }
    char* ret_sqlite3_expanded_sql_sinwj = sqlite3_expanded_sql(NULL);
    if (ret_sqlite3_expanded_sql_sinwj == NULL){
    	return 0;
    }
    sqlite3_int64 ret_sqlite3_last_insert_rowid_ysncc = sqlite3_last_insert_rowid(db);
    sqlite3_int64 ret_sqlite3_memory_highwater_utxtx = sqlite3_memory_highwater(-1);
    int ret_sqlite3_deserialize_hdbjr = sqlite3_deserialize(db, (const char *)ret_sqlite3_malloc_smvlt, (unsigned char *)ret_sqlite3_expanded_sql_sinwj, ret_sqlite3_last_insert_rowid_ysncc, ret_sqlite3_memory_highwater_utxtx, size);
    if (ret_sqlite3_deserialize_hdbjr < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
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

    LLVMFuzzerTestOneInput_584(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
