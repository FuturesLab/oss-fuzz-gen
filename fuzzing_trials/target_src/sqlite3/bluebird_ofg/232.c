#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int LLVMFuzzerTestOneInput_232(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to split into meaningful parts
    if (size < 2) {
        return 0;
    }

    // Initialize SQLite variables
    sqlite3 *db = NULL;
    int rc;

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare a null-terminated string from the fuzzing data
    size_t str_size = size - 1;
    char *client_data_key = (char *)malloc(str_size + 1);
    if (client_data_key == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(client_data_key, data, str_size);
    client_data_key[str_size] = '\0';

    // Execute SQL command
    char *errMsg = 0;
    rc = sqlite3_exec(db, client_data_key, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
    }

    // Clean up
    free(client_data_key);
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

    LLVMFuzzerTestOneInput_232(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
