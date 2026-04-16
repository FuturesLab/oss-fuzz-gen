#include <stddef.h>  // For size_t
#include <stdlib.h>
#include <sys/stat.h>  // For NULL
#include <stdint.h>
#include "sqlite3.h"
#include <string.h>  // For strlen

int LLVMFuzzerTestOneInput_906(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;

    // Attempt to open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Exit if the database couldn't be opened
    }

    // If there's data, attempt to execute it as an SQL statement
    if (size > 0) {
        // Ensure the data is null-terminated before passing to sqlite3_exec
        char *sql = (char *)malloc(size + 1);
        if (sql == NULL) {
            sqlite3_close(db);
            return 0; // Exit if memory allocation fails
        }
        memcpy(sql, data, size);
        sql[size] = '\0'; // Null-terminate the string

        char *errMsg = 0;
        rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            sqlite3_free(errMsg);
        }

        free(sql); // Free the allocated memory
    }

    // Call the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_open to sqlite3_wal_autocheckpoint
    int ret_sqlite3_wal_autocheckpoint_bfjjy = sqlite3_wal_autocheckpoint(db, 0);
    if (ret_sqlite3_wal_autocheckpoint_bfjjy < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    int errno_result = sqlite3_system_errno(db);

    // Clean up and close the database
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

    LLVMFuzzerTestOneInput_906(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
