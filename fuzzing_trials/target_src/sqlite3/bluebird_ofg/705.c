#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_705(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to be used as a C string
    char *sql_query = (char *)malloc(size + 1);
    if (sql_query == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(sql_query, data, size);
    sql_query[size] = '\0';

    // Call the function-under-test
    sqlite3_complete(sql_query);

    // Free allocated memory
    free(sql_query);

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

    LLVMFuzzerTestOneInput_705(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
