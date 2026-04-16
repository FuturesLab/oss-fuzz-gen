#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_825(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    // Open a new database connection in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    if (size > 0) {
        // Ensure the input data is null-terminated to prevent buffer overflow
        char *sql = (char *)malloc(size + 1);
        if (!sql) {
            sqlite3_close(db);
            return 0;
        }
        memcpy(sql, data, size);
        sql[size] = '\0';

        // Execute the input data as an SQL statement
        rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
        
        // Free the allocated SQL statement
        free(sql);

        // Free the error message if it was allocated
        if (errMsg) {
            sqlite3_free(errMsg);
        }
    }

    // Close the database connection

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_open to sqlite3_get_table
    sqlite3_free((void *)db);
    char* ret_sqlite3_expanded_sql_dyuru = sqlite3_expanded_sql(NULL);
    if (ret_sqlite3_expanded_sql_dyuru == NULL){
    	return 0;
    }
    int kuhpoisz = 0;
    int ushnikju = -1;
    int ret_sqlite3_get_table_fmrwc = sqlite3_get_table(db, db, (char ***)"r", &kuhpoisz, &ushnikju, &ret_sqlite3_expanded_sql_dyuru);
    if (ret_sqlite3_get_table_fmrwc < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
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

    LLVMFuzzerTestOneInput_825(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
