#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_550(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;
    const char *dbName = "test.db";
    const char *schema = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value TEXT);";
    unsigned char *serializedData;
    sqlite3_int64 serializedSize;
    unsigned int flags = 0;

    // Initialize the SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        return 0;
    }

    // Execute a simple schema
    rc = sqlite3_exec(db, schema, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Ensure data is not NULL and has a valid size
    if (size > 0 && data != NULL) {
        // Prepare a statement from the input data
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, (const char *)data, (int)size, &stmt, NULL);
        if (rc == SQLITE_OK && stmt != NULL) {
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }
    }

    // Call the function-under-test
    serializedData = sqlite3_serialize(db, dbName, &serializedSize, flags);

    // Free the serialized data if it was allocated
    if (serializedData) {
        sqlite3_free(serializedData);
    }

    // Close the SQLite database
    sqlite3_close(db);

    return 0;
}

#ifdef __cplusplus
}
#endif
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

    LLVMFuzzerTestOneInput_550(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
