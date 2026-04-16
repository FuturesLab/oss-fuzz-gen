#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "sqlite3.h"

static int authorizerCallback(void *pUserData, int action, const char *arg1, const char *arg2, const char *arg3, const char *arg4) {
    return SQLITE_OK; // Allow all actions
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0; // No-op callback
}

int LLVMFuzzerTestOneInput_274(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    sqlite3 *db;
    char *errMsg = 0;
    char *sql = (char *)malloc(Size + 1);
    if (!sql) {
        return 0;
    }
    memcpy(sql, Data, Size);
    sql[Size] = '\0'; // Ensure null-termination

    int rc;

    // Open a database connection
    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_open
    rc = sqlite3_open((const char *)"r", &db);
    // End mutation: Producer.REPLACE_ARG_MUTATOR
    if (rc != SQLITE_OK) {
        free(sql);
        return 0;
    }

    // Execute SQL
    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
    }

    // Set authorizer

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_exec to sqlite3_open
    int ret_sqlite3_open_gpblf = sqlite3_open(NULL, &db);
    if (ret_sqlite3_open_gpblf < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_open to sqlite3_prepare16_v2
    int ret_sqlite3_error_offset_lpyvo = sqlite3_error_offset(db);
    if (ret_sqlite3_error_offset_lpyvo < 0){
    	return 0;
    }
    const void* ret_sqlite3_errmsg16_balab = sqlite3_errmsg16(db);
    if (ret_sqlite3_errmsg16_balab == NULL){
    	return 0;
    }
    int ret_sqlite3_prepare16_v2_swqro = sqlite3_prepare16_v2(db, (const void *)db, Size, NULL, (const void **)&db);
    if (ret_sqlite3_prepare16_v2_swqro < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    rc = sqlite3_set_authorizer(db, authorizerCallback, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        free(sql);
        return 0;
    }

    // Table column metadata
    const char *dataType;
    const char *collSeq;
    int notNull;
    int primaryKey;
    int autoinc;
    rc = sqlite3_table_column_metadata(db, "main", "dummy_table", "dummy_column", &dataType, &collSeq, &notNull, &primaryKey, &autoinc);

    // Test control
//    rc = sqlite3_test_control(SQLITE_TESTCTRL_FIRST, db);

    // Malloc
    void *ptr = sqlite3_malloc(Size);
    if (ptr) {
        memcpy(ptr, Data, Size);
        sqlite3_free(ptr);
    }

    // Close the database connection
    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_close with sqlite3_db_release_memory
    sqlite3_db_release_memory(db);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR
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

    LLVMFuzzerTestOneInput_274(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
