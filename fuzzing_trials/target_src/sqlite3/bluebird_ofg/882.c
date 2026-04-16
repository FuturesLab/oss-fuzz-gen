#include <stdint.h>
#include <stddef.h>  // Include this for size_t
#include "sqlite3.h"
#include <stdlib.h>
#include <sys/stat.h>  // Include this for malloc and free

int LLVMFuzzerTestOneInput_882(const uint8_t *data, size_t size) {
    // Initialize SQLite library
    if (sqlite3_initialize() != SQLITE_OK) {
        return 0; // If initialization fails, return 0 to continue fuzzing
    }

    // Create an in-memory database
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        sqlite3_shutdown();
        return 0; // If opening the database fails, return 0 to continue fuzzing
    }

    // Allocate memory for the null-terminated input data
    char *sql = (char *)malloc(size + 1);
    if (!sql) {
        sqlite3_close(db);
        sqlite3_shutdown();
        return 0; // If memory allocation fails, return 0 to continue fuzzing
    }

    // Copy the input data and null-terminate it
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute the input data as an SQL statement
    char *errMsg = 0;
    sqlite3_exec(db, sql, 0, 0, &errMsg);

    // Free the allocated memory for the SQL statement
    free(sql);

    // Free any error message allocated by sqlite3_exec
    if (errMsg) {
        sqlite3_free(errMsg);
    }

    // Close the database connection
    sqlite3_close(db);

    // Shutdown SQLite library
    sqlite3_shutdown();

    // Return 0 to indicate the fuzzer should continue
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

    LLVMFuzzerTestOneInput_882(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
