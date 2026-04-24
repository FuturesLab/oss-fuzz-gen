#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Function-under-test declaration
long long hts_parse_decimal(const char *, char **, int);

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for testing
    if (size < 2) {
        return 0;
    }

    // Allocate memory for the input string and ensure it's null-terminated
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Allocate memory for the end pointer
    char *endptr = NULL;

    // Use a fixed integer value for the third parameter
    int fixed_value = 10;

    // Call the function-under-test
    long long result = hts_parse_decimal(input, &endptr, fixed_value);

    // Free allocated memory
    free(input);

    // Return 0 to indicate successful execution
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

    LLVMFuzzerTestOneInput_52(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
