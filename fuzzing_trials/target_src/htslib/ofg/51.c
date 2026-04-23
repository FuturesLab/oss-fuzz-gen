#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// Function-under-test declaration
long long hts_parse_decimal(const char *str, char **endptr, int flags);

int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to be used as a string
    char *input = (char *)malloc(size + 1);
    if (!input) {
        return 0; // Return if memory allocation fails
    }
    // Copy data and null-terminate
    for (size_t i = 0; i < size; ++i) {
        input[i] = (char)data[i];
    }
    input[size] = '\0';

    // Prepare variables for the function call
    char *endptr = NULL;
    int flags = 0; // Example flag, adjust as needed

    // Call the function-under-test
    long long result = hts_parse_decimal(input, &endptr, flags);

    // Use the result and endptr in some way to avoid compiler optimizations
    (void)result;
    (void)endptr;

    // Clean up
    free(input);

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

    LLVMFuzzerTestOneInput_51(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
