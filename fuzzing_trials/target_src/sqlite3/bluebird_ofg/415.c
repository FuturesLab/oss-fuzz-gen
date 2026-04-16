#include <stdint.h>
#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int LLVMFuzzerTestOneInput_415(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    char *errMsg = NULL;
    char *expanded_sql = NULL;
    
    // Initialize SQLite database in memory
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }
    
    // Create a dummy table to prepare a statement
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    if (sqlite3_exec(db, createTableSQL, NULL, NULL, &errMsg) != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }
    
    // Prepare a statement based on the input data
    if (size > 0) {
        char *query = (char *)malloc(size + 1);
        if (query == NULL) {
            sqlite3_close(db);
            return 0;
        }
        
        memcpy(query, data, size);
        query[size] = '\0'; // Ensure null-termination
        
        if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
            free(query);
            sqlite3_close(db);
            return 0;
        }
        
        free(query);
    }
    
    // Call the function-under-test
    expanded_sql = sqlite3_expanded_sql(stmt);
    
    // If expanded_sql is not NULL, free it
    if (expanded_sql != NULL) {
        sqlite3_free(expanded_sql);
    }
    
    // Finalize the statement and close the database
    if (stmt != NULL) {
        sqlite3_finalize(stmt);
    }
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

    LLVMFuzzerTestOneInput_415(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
