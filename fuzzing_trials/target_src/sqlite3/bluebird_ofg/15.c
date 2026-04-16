#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Ensure size is at least 1 to avoid reallocating to size 0
    if (size < 1) {
        return 0;
    }

    // Allocate initial memory block
    void *initial_memory = malloc(size);
    if (initial_memory == NULL) {
        return 0; // Memory allocation failed
    }

    // Copy data to the initial memory block
    memcpy(initial_memory, data, size);

    // Call the function-under-test with the initial memory block and a new size
    int new_size = (int)size * 2; // Example new size
    if (new_size <= 0) {
        free(initial_memory);
        return 0; // Avoid reallocating with invalid size
    }

    // Use sqlite3_malloc to allocate new memory block instead of reallocating
    void *new_memory = sqlite3_malloc(new_size);
    if (new_memory != NULL) {
        // Copy the initial memory block to the new memory block
        memcpy(new_memory, initial_memory, size);

        // Initialize SQLite database in memory
        sqlite3 *db;
        if (sqlite3_open(":memory:", &db) == SQLITE_OK) {
            // Create a SQL statement from the input data
            char *sql = (char *)malloc(size + 1);
            if (sql != NULL) {
                memcpy(sql, data, size);
                sql[size] = '\0'; // Null-terminate the string

                // Execute the SQL statement
                char *errMsg = NULL;
                sqlite3_exec(db, sql, 0, 0, &errMsg);

                // Free the SQL string
                free(sql);
            }

            // Close the SQLite database
            sqlite3_close(db);
        }

        // Free the new memory block
        sqlite3_free(new_memory);
    }

    // Free the initial memory block
    free(initial_memory);

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

    LLVMFuzzerTestOneInput_15(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
