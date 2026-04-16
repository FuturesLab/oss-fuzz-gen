#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_885(const uint8_t *data, size_t size) {
    if (size < 2) return 0; // Ensure there's enough data for the function parameters

    sqlite3_str *str;
    int count = data[0]; // Use the first byte of data for the count
    char c = (char)data[1]; // Use the second byte of data for the char

    // Initialize the sqlite3_str object
    str = sqlite3_str_new(NULL);

    // Call the function-under-test
    sqlite3_str_appendchar(str, count, c);

    // Clean up
    sqlite3_str_finish(str);

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

    LLVMFuzzerTestOneInput_885(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
