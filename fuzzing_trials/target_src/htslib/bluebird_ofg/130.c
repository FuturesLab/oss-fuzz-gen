#include <sys/stat.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Assuming sam_hdr_t is defined somewhere in the included headers
typedef struct {
    // Dummy structure for demonstration purposes
    int dummy;
} sam_hdr_t;

// Assuming the function sam_hdr_parse is defined somewhere in the included headers
sam_hdr_t * sam_hdr_parse(size_t len, const char *str);

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Ensure the data is null-terminated
    char *input_str = (char *)malloc(size + 1);
    if (input_str == NULL) {
        return 0;
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';

    // Call the function-under-test
    sam_hdr_t *result = sam_hdr_parse(size, input_str);

    // Clean up
    free(input_str);

    // Assuming there's a way to free or handle the result if needed
    // free_sam_hdr(result); // Uncomment if a function to free sam_hdr_t is available

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

    LLVMFuzzerTestOneInput_130(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
