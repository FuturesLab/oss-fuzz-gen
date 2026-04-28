#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

extern "C" {
    // Since icalmemory.h does not exist, we need to declare the function prototype here
    char *icalmemory_strdup(const char *str);
}

extern "C" int LLVMFuzzerTestOneInput_84(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to be used as a C-string
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) {
        return 0; // If memory allocation fails, exit
    }
    memcpy(inputString, data, size);
    inputString[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    char *duplicatedString = icalmemory_strdup(inputString);

    // Free the duplicated string if it was successfully created
    if (duplicatedString != NULL) {
        free(duplicatedString);
    }

    // Free the input string
    free(inputString);

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

    LLVMFuzzerTestOneInput_84(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
