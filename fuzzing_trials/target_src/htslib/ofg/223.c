#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Assuming the function is declared in a header file
int hts_resize_array_(size_t, size_t, size_t, void *, void **, int, const char *);

int LLVMFuzzerTestOneInput_223(const uint8_t *data, size_t size) {
    if (size < sizeof(size_t) * 3 + sizeof(int) + 1) {
        return 0; // Not enough data to fill all parameters
    }

    size_t pos = 0;

    // Extracting parameters from the input data
    size_t param1 = *(size_t *)(data + pos);
    pos += sizeof(size_t);

    size_t param2 = *(size_t *)(data + pos);
    pos += sizeof(size_t);

    size_t param3 = *(size_t *)(data + pos);
    pos += sizeof(size_t);

    int param6 = *(int *)(data + pos);
    pos += sizeof(int);

    // Ensure parameters are within reasonable bounds to avoid excessive memory allocation
    if (param1 > 1024 || param2 > 1024 || param3 > 1024) {
        return 0; // Avoid excessive memory allocation
    }

    // Allocate memory for void* and void** parameters
    void *param4 = malloc(param1 * param2 * param3);
    if (param4 == NULL) {
        return 0; // Memory allocation failed
    }

    void **param5 = (void **)malloc(sizeof(void *));
    if (param5 == NULL) {
        free(param4);
        return 0; // Memory allocation failed
    }
    *param5 = param4;

    // Extract a string for the last parameter
    size_t remaining_size = size - pos;
    char *param7 = (char *)malloc(remaining_size + 1);
    if (param7 == NULL) {
        free(param4);
        free(param5);
        return 0; // Memory allocation failed
    }
    memcpy(param7, data + pos, remaining_size);
    param7[remaining_size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    hts_resize_array_(param1, param2, param3, param4, param5, param6, param7);

    // Clean up
    free(param4);
    free(param5);
    free(param7);

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

    LLVMFuzzerTestOneInput_223(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
