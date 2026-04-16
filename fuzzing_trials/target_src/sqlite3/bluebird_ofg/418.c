#include <stdint.h>
#include "sqlite3.h"
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int LLVMFuzzerTestOneInput_418(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    const void *tail = NULL;
    int rc;

    // Open a temporary in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the input data is not NULL and size is non-zero
    if (data == NULL || size == 0) {
        sqlite3_close(db);
        return 0;
    }

    // Allocate a buffer for the SQL statement and ensure it's null-terminated
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0'; // Null-terminate the SQL statement

    // Use the input data as a SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &tail);

    // Finalize the statement if it was successfully prepared
    if (rc == SQLITE_OK && stmt != NULL) {
        sqlite3_finalize(stmt);
    }

    // Free the allocated SQL buffer
    free(sql);

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

    LLVMFuzzerTestOneInput_418(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
