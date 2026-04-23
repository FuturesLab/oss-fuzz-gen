#include <sys/stat.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern const char *hts_parse_reg(const char *, int *, int *);

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a string and two integers
    if (size < 3) {
        return 0;
    }

    // Create a null-terminated string from the data
    char *region = (char *)malloc(size + 1);
    if (region == NULL) {
        return 0;
    }
    memcpy(region, data, size);
    region[size] = '\0';

    // Initialize the integer pointers
    int beg = 0;
    int end = 0;

    // Call the function-under-test
    const char *result = hts_parse_reg(region, &beg, &end);

    // Clean up
    free(region);

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

    LLVMFuzzerTestOneInput_18(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
