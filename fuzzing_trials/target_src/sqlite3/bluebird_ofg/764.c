#include <stdint.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int LLVMFuzzerTestOneInput_764(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    char *errMsg = 0;

    // Create an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        return 0; // If opening the database fails, exit early
    }

    // Execute a simple SQL statement to ensure the database is initialized
    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value TEXT);", NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Ensure the input data is null-terminated for safe usage with %Q
    char *safeData = (char *)malloc(size + 1);
    if (!safeData) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(safeData, data, size);
    safeData[size] = '\0';

    // Prepare a SQL statement using the input data
    char *sql = sqlite3_mprintf("INSERT INTO test (value) VALUES (%Q);", safeData);
    free(safeData);

    // Execute the SQL statement
    rc = sqlite3_exec(db, sql, NULL, 0, &errMsg);
    sqlite3_free(sql);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    sqlite3_db_cacheflush(db);

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

    LLVMFuzzerTestOneInput_764(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
