#include <sys/stat.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Function signature for the function-under-test
int hfile_list_schemes(const char *, const char **, int *);

// LLVMFuzzerTestOneInput function to fuzz hfile_list_schemes
int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for at least one character string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the string input and ensure it is null-terminated
    char *input_str = (char *)malloc(size + 1);
    if (input_str == NULL) {
        return 0;
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';

    // Prepare the output parameters for the function-under-test
    const char *schemes[10]; // Assuming a maximum of 10 schemes for testing
    int count = 0;

    // Call the function-under-test
    hfile_list_schemes(input_str, schemes, &count);

    // Clean up
    free(input_str);

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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_55(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
