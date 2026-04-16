#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <stdlib.h>
#include <sys/stat.h>  // Include for NULL
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_276(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    char *errMsg = NULL;
    int rc;

    // Open an in-memory database
    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_open
    rc = sqlite3_open((const char *)"w", &db);
    // End mutation: Producer.REPLACE_ARG_MUTATOR
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare an SQL statement using the input data
    // Note: The input data is not null-terminated, so we need to handle it carefully
    char *sql = sqlite3_mprintf("%.*s", (int)size, data);

    // Execute the SQL statement
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    
    // Free the allocated SQL string
    sqlite3_free(sql);

    // Check for errors
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
    }

    // Close the database
    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_close with sqlite3_changes
    sqlite3_changes(db);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR

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

    LLVMFuzzerTestOneInput_276(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
