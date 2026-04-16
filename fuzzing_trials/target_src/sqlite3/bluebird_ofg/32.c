#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

// Define a function pointer type for an infinite loop function
typedef void (*infinite_loop_func)(void);

// Dummy infinite loop function
int dummy_infinite_loop_32(void) {
    while (1) {
        // Infinite loop
    }
    return 0;
}

// Fuzzer entry point
int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errMsg = 0;

    // Initialize SQLite3 database in memory
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Ensure the data is null-terminated to prevent buffer overflow
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0'; // Null-terminate the string

    // Execute SQL command
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        sqlite3_free(errMsg);
    }

    // Free the allocated memory for SQL command
    free(sql);

    // Close the SQLite3 database
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

    LLVMFuzzerTestOneInput_32(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
