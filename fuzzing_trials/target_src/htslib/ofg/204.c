#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function-under-test declaration
char * sam_open_mode_opts(const char *mode, const char *type, const char *options);

int LLVMFuzzerTestOneInput_204(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to split into three parts
    if (size < 3) {
        return 0;
    }

    // Divide the input data into three parts for mode, type, and options
    size_t part_size = size / 3;
    size_t remainder = size % 3;

    // Allocate memory for the strings
    char *mode = (char *)malloc(part_size + 1);
    char *type = (char *)malloc(part_size + 1);
    char *options = (char *)malloc(part_size + remainder + 1);

    // Copy data into the strings and null-terminate them
    memcpy(mode, data, part_size);
    mode[part_size] = '\0';

    memcpy(type, data + part_size, part_size);
    type[part_size] = '\0';

    memcpy(options, data + 2 * part_size, part_size + remainder);
    options[part_size + remainder] = '\0';

    // Call the function-under-test
    char *result = sam_open_mode_opts(mode, type, options);

    // Free the allocated memory
    free(mode);
    free(type);
    free(options);

    // Free the result if it's dynamically allocated
    free(result);

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

    LLVMFuzzerTestOneInput_204(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
