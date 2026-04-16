#include <stdint.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int LLVMFuzzerTestOneInput_567(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt = NULL;
    const void *tail = NULL;
    int rc;

    // Open a temporary in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the input data is not empty and has a reasonable size
    if (size > 0 && size < 1000) {
        // Null-terminate the input data to prevent buffer overflow
        uint8_t *null_terminated_data = (uint8_t *)malloc(size + 1);
        if (null_terminated_data == NULL) {
            sqlite3_close(db);
            return 0;
        }
        memcpy(null_terminated_data, data, size);
        null_terminated_data[size] = '\0';

        // Prepare the SQL statement using the null-terminated input data
        rc = sqlite3_prepare_v2(db, (const char *)null_terminated_data, (int)size, &stmt, &tail);

        // Finalize the statement if it was prepared successfully
        if (stmt != NULL) {
            sqlite3_finalize(stmt);
        }

        // Free the allocated memory
        free(null_terminated_data);
    }

    // Close the database connection
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

    LLVMFuzzerTestOneInput_567(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
