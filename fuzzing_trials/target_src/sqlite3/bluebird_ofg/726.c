#include <stdint.h>
#include "sqlite3.h"
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int LLVMFuzzerTestOneInput_726(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    char *filename = NULL;

    // Ensure the data is null-terminated and non-empty
    if (size > 0) {
        filename = (char *)malloc(size + 1);
        if (filename == NULL) {
            return 0;
        }
        memcpy(filename, data, size);
        filename[size] = '\0'; // Null-terminate the string

        // Call the function-under-test
        int result = sqlite3_open(filename, &db);

        // Close the database if it was opened successfully
        if (result == SQLITE_OK) {
            sqlite3_close(db);
        }

        free(filename);
    }

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

    LLVMFuzzerTestOneInput_726(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
