#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_744(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to split into two strings
    if (size < 2) {
        return 0;
    }

    // Find a midpoint to split the input data into two strings
    size_t midpoint = size / 2;

    // Allocate memory for the two strings and ensure they are null-terminated
    char *str1 = (char *)malloc(midpoint + 1);
    char *str2 = (char *)malloc(size - midpoint + 1);

    if (str1 == NULL || str2 == NULL) {
        free(str1);
        free(str2);
        return 0;
    }

    // Copy data into the strings and null-terminate them
    memcpy(str1, data, midpoint);
    str1[midpoint] = '\0';

    memcpy(str2, data + midpoint, size - midpoint);
    str2[size - midpoint] = '\0';

    // Call the function under test
    int result = sqlite3_strglob(str1, str2);

    // Free allocated memory
    free(str1);
    free(str2);

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

    LLVMFuzzerTestOneInput_744(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
