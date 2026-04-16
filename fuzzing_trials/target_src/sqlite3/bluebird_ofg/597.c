#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_597(const uint8_t *data, size_t size) {
    // Ensure there is data to process
    if (size == 0) {
        return 0;
    }

    // Open an in-memory SQLite database
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Use the provided data as the SQL input
    const char *sql = (const char *)data;

    // Prepare the SQL statement
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, (int)size, &stmt, NULL);

    // Finalize the statement if it was prepared
    if (rc == SQLITE_OK) {
        sqlite3_finalize(stmt);
    }

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

    LLVMFuzzerTestOneInput_597(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
