#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

// Function-under-test declaration
char *sam_open_mode_opts(const char *path, const char *mode, const char *opts);

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract three non-NULL strings
    if (size < 3) {
        return 0;
    }

    // Split the input data into three parts
    size_t part_size = size / 3;
    size_t remainder = size % 3;

    // Allocate memory for the strings
    char *path = (char *)malloc(part_size + 1);
    char *mode = (char *)malloc(part_size + 1);
    char *opts = (char *)malloc(part_size + remainder + 1);

    // Copy data into the strings and null-terminate them
    memcpy(path, data, part_size);
    path[part_size] = '\0';

    memcpy(mode, data + part_size, part_size);
    mode[part_size] = '\0';

    memcpy(opts, data + 2 * part_size, part_size + remainder);
    opts[part_size + remainder] = '\0';

    // Call the function-under-test
    char *result = sam_open_mode_opts(path, mode, opts);

    // Free the allocated memory
    free(path);
    free(mode);
    free(opts);

    // Free the result if it's dynamically allocated (assuming it needs to be freed)
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_37(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
