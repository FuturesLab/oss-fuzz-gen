#include <stdint.h>
#include <stddef.h> // Include for size_t
#include <stdlib.h>
#include <sys/stat.h> // Include for NULL
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_546(const uint8_t *data, size_t size) {
    // Initialize SQLite
    int result = sqlite3_initialize();
    if (result != SQLITE_OK) {
        return 0;
    }

    // Create an in-memory database
    sqlite3 *db;
    result = sqlite3_open(":memory:", &db);
    if (result != SQLITE_OK) {
        sqlite3_shutdown();
        return 0;
    }

    // Prepare a SQL statement using the fuzz input
    sqlite3_stmt *stmt;
    result = sqlite3_prepare_v2(db, (const char *)data, size, &stmt, NULL);

    // Finalize the statement if it was prepared
    if (result == SQLITE_OK && stmt != NULL) {
        sqlite3_finalize(stmt);
    }

    // Close the database
    sqlite3_close(db);

    // Shutdown SQLite
    sqlite3_shutdown();

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

    LLVMFuzzerTestOneInput_546(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
