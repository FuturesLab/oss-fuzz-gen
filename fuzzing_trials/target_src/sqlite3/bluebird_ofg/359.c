#include <stdint.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_359(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    const void *result;
    int columnIndex = 0;

    // Open an in-memory SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // If opening the database fails, return early
    }

    // Prepare a statement using the SQLite library
    if (sqlite3_prepare_v2(db, (const char *)data, (int)size, &stmt, NULL) == SQLITE_OK) {
        // Execute the statement to ensure a row is available
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            // Call the function-under-test
            result = sqlite3_column_text16(stmt, columnIndex);

            // Optionally, you can add checks or further processing on 'result'
            if (result != NULL) {
                // Do something with the result if needed
            }
        }

        // Finalize the statement to clean up resources
        sqlite3_finalize(stmt);
    }

    // Close the SQLite database
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

    LLVMFuzzerTestOneInput_359(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
