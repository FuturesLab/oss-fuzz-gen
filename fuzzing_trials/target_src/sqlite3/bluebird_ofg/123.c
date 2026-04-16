#include <stdint.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <sys/stat.h>

int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int checkpoint_threshold = 1000; // Arbitrary non-zero value for testing
    int result;

    // Open an in-memory SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Convert the input data to a string
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute the SQL command
    char *errMsg = NULL;
    sqlite3_exec(db, sql, 0, 0, &errMsg);

    // Call the function-under-test
    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_wal_autocheckpoint with sqlite3_db_config
    result = sqlite3_db_config(db, checkpoint_threshold);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR

    // Free resources
    sqlite3_free(errMsg);
    free(sql);
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

    LLVMFuzzerTestOneInput_123(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
