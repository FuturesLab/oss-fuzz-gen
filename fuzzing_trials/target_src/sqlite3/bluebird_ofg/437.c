#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_437(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    const void *tail = NULL;
    int rc;

    // Open a temporary in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK || db == NULL) {
        return 0; // Failed to open the database
    }

    // Ensure the input data is null-terminated to prevent buffer overflow
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0; // Failed to allocate memory
    }
    memcpy(sql, data, size);
    sql[size] = '\0'; // Null-terminate

    // Prepare a SQL statement using the input data
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &tail);

    // Finalize the statement if it was prepared
    if (stmt != NULL) {
        sqlite3_finalize(stmt);
    }

    // Free the allocated memory
    free(sql);

    // Close the database
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

    LLVMFuzzerTestOneInput_437(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
