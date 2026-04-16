#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int LLVMFuzzerTestOneInput_279(const uint8_t *data, size_t size) {
    // Call the function-under-test
    int version = sqlite3_libversion_number();

    // Use the returned version number in some way to avoid compiler optimizations
    if (version == 0) {
        return 0;
    }

    // Use the input data in some way to maximize fuzzing result
    if (size > 0 && data != NULL) {
        sqlite3 *db;
        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_open
        int rc = sqlite3_open((const char *)"w", &db);
        // End mutation: Producer.REPLACE_ARG_MUTATOR
        if (rc == SQLITE_OK) {
            // Allocate memory for the SQL statement and ensure it's null-terminated
            char *sql = (char *)malloc(size + 1);
            if (sql == NULL) {
                sqlite3_close(db);
                return 0;
            }
            memcpy(sql, data, size);
            sql[size] = '\0'; // Null-terminate the SQL statement

            // Attempt to create a table using the input data as SQL statement
            char *errMsg = 0;
            sqlite3_exec(db, sql, 0, 0, &errMsg);
            sqlite3_free(errMsg);
            // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_close with sqlite3_total_changes
            sqlite3_total_changes(db);
            // End mutation: Producer.REPLACE_FUNC_MUTATOR

            // Free the allocated memory for the SQL statement
            free(sql);
        }
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

    LLVMFuzzerTestOneInput_279(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
