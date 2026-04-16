#include <stdint.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int LLVMFuzzerTestOneInput_217(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a sample table and insert some data
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    sqlite3_exec(db, createTableSQL, 0, 0, 0);

    // Insert data based on provided fuzzing input
    if (size > 0) {
        char *insertSQL = (char *)malloc(size + 50);
        if (insertSQL != NULL) {
            snprintf(insertSQL, size + 50, "INSERT INTO test (value) VALUES ('%.*s');", (int)size, data);
            sqlite3_exec(db, insertSQL, 0, 0, 0);
            free(insertSQL);
        }
    }

    // Call the function-under-test
    sqlite3_int64 changes = sqlite3_total_changes64(db);

    // Clean up
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

    LLVMFuzzerTestOneInput_217(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
