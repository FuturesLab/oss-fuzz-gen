#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <stdlib.h>
#include <sys/stat.h>  // Include for NULL
#include "sqlite3.h"
#include <string.h>  // Include for memcpy

int LLVMFuzzerTestOneInput_665(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    char *errMsg = NULL;

    // Initialize the SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // If opening the database fails, return early
    }

    // Ensure the database pointer is not NULL before calling the function
    if (db != NULL) {
        // Allocate memory for the SQL statement
        char *sql = (char *)malloc(size + 1);
        if (sql == NULL) {
            sqlite3_close_v2(db);
            return 0;
        }

        // Copy the fuzz input into the SQL statement buffer
        memcpy(sql, data, size);
        sql[size] = '\0'; // Null-terminate the string

        // Execute the SQL statement
        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of sqlite3_exec
        rc = sqlite3_exec(db, (const char *)"r", 0, 0, &errMsg);
        // End mutation: Producer.REPLACE_ARG_MUTATOR
        
        // Free the allocated memory for the SQL statement
        free(sql);

        // Free the error message if it was set
        if (errMsg != NULL) {
            sqlite3_free(errMsg);
        }

        // Close the database
        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_close_v2 with sqlite3_changes
        sqlite3_changes(db);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR
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

    LLVMFuzzerTestOneInput_665(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
