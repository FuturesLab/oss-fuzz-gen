#include <stdint.h>
#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int LLVMFuzzerTestOneInput_881(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    char *errMsg = 0;

    // Allocate a buffer with an extra byte for the null terminator
    char *sql = (char *)malloc(size + 1);
    if (!sql) {
        fprintf(stderr, "Memory allocation failed\n");
        return 0;
    }

    // Copy the input data to the buffer and null-terminate it
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Open a new database connection. ":memory:" creates a new database in RAM.
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        free(sql);
        return 0;
    }

    // Execute some SQL statement to potentially generate an error
    // Using the input data as the SQL statement

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_open to sqlite3_load_extension
    char* ret_sqlite3_expanded_sql_lwroo = sqlite3_expanded_sql(NULL);
    if (ret_sqlite3_expanded_sql_lwroo == NULL){
    	return 0;
    }
    void* ret_sqlite3_malloc_izywn = sqlite3_malloc(-1);
    if (ret_sqlite3_malloc_izywn == NULL){
    	return 0;
    }
    void* ret_sqlite3_malloc_oahin = sqlite3_malloc(0);
    if (ret_sqlite3_malloc_oahin == NULL){
    	return 0;
    }
    int ret_sqlite3_load_extension_bppvc = sqlite3_load_extension(db, ret_sqlite3_expanded_sql_lwroo, (const char *)ret_sqlite3_malloc_izywn, (char **)&ret_sqlite3_malloc_oahin);
    if (ret_sqlite3_load_extension_bppvc < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        // Call the function-under-test
        const char *error_message = sqlite3_errmsg(db);
        // Print the error message for debugging purposes
        fprintf(stderr, "SQL error: %s\n", error_message);

        // Free the error message if it was allocated
        if (errMsg) {
            sqlite3_free(errMsg);
        }
    }

    // Close the database connection
    sqlite3_close(db);

    // Free the allocated buffer
    free(sql);

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

    LLVMFuzzerTestOneInput_881(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
