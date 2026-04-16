#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int LLVMFuzzerTestOneInput_497(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    unsigned char *serialized_data;
    sqlite3_int64 serialized_size;
    unsigned int flags = 0;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the data is null-terminated and use it as the schema name
    char *schema_name = (char *)malloc(size + 1);
    if (schema_name == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(schema_name, data, size);
    schema_name[size] = '\0';

    // Call the function-under-test
    serialized_data = sqlite3_serialize(db, schema_name, &serialized_size, flags);

    // Free the allocated resources
    free(schema_name);
    if (serialized_data != NULL) {
        sqlite3_free(serialized_data);
    }
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

    LLVMFuzzerTestOneInput_497(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
