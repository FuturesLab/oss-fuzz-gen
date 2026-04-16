#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "sqlite3.h"

// Function to execute a SQL command
static void execute_sql(sqlite3 *db, const char *sql) {
    char *errMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
    }
}

int LLVMFuzzerTestOneInput_476(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;

    // Open a new in-memory database
    const char lwzpauru[1024] = "zducm";
    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_open
    rc = sqlite3_open(lwzpauru, &db);
    // End mutation: Producer.REPLACE_ARG_MUTATOR
    if (rc != SQLITE_OK) {
        return 0; // If opening the database failed, return immediately
    }

    // Ensure the database pointer is not NULL
    if (db != NULL) {
        // Attempt to execute the input data as SQL command
        char *sql = (char *)malloc(size + 1);
        if (sql != NULL) {
            memcpy(sql, data, size);
            sql[size] = '\0'; // Null-terminate the input data
            execute_sql(db, sql);
            free(sql);
        }

        // Close the database
        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_close with sqlite3_changes
        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_changes with sqlite3_error_offset
        sqlite3_error_offset(db);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR
        // End mutation: Producer.REPLACE_FUNC_MUTATOR
    
        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_error_offset to sqlite3_table_column_metadata
        void* ret_sqlite3_malloc_uozux = sqlite3_malloc(size);
        if (ret_sqlite3_malloc_uozux == NULL){
        	return 0;
        }
        void* ret_sqlite3_malloc_kbfyr = sqlite3_malloc(size);
        if (ret_sqlite3_malloc_kbfyr == NULL){
        	return 0;
        }
        sqlite3_free((void *)db);
        void* ret_sqlite3_malloc_qrzjv = sqlite3_malloc(0);
        if (ret_sqlite3_malloc_qrzjv == NULL){
        	return 0;
        }
        const char njquthcm[1024] = "vfbvw";
        int cvwbuxtc = 0;
        int ybhjnubh = 0;
        int ret_sqlite3_table_column_metadata_dowlt = sqlite3_table_column_metadata(db, (const char *)ret_sqlite3_malloc_uozux, njquthcm, (const char *)ret_sqlite3_malloc_kbfyr, db, (const char **)&ret_sqlite3_malloc_qrzjv, NULL, &cvwbuxtc, &ybhjnubh);
        if (ret_sqlite3_table_column_metadata_dowlt < 0){
        	return 0;
        }
        // End mutation: Producer.APPEND_MUTATOR
        
}

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

    LLVMFuzzerTestOneInput_476(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
