#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

// Callback function for sqlite3_exec
static int callback_245(void *data, int argc, char **argv, char **azColName) {
    return 0;
}

int LLVMFuzzerTestOneInput_245(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errMsg = NULL;
    int rc;

    // Initialize database connection
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the input data is null-terminated for use as a string
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute the SQL command
    sqlite3_exec(db, sql, callback_245, NULL, &errMsg);

    // Clean up
    if (errMsg) {
        sqlite3_free(errMsg);
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_exec to sqlite3_create_filename
    char* ret_sqlite3_str_finish_llpds = sqlite3_str_finish(NULL);
    if (ret_sqlite3_str_finish_llpds == NULL){
    	return 0;
    }
    char* ret_sqlite3_str_finish_rxuco = sqlite3_str_finish(NULL);
    if (ret_sqlite3_str_finish_rxuco == NULL){
    	return 0;
    }
    char *vipaugrz[1024] = {"kpitx", NULL};
    sqlite3_free_table(vipaugrz);
    unsigned int ret_sqlite3_value_subtype_hwfhk = sqlite3_value_subtype(NULL);
    if (ret_sqlite3_value_subtype_hwfhk < 0){
    	return 0;
    }
    sqlite3_filename ret_sqlite3_create_filename_toagy = sqlite3_create_filename(ret_sqlite3_str_finish_llpds, ret_sqlite3_str_finish_rxuco, *vipaugrz, (int )ret_sqlite3_value_subtype_hwfhk, &errMsg);
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

    LLVMFuzzerTestOneInput_245(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
