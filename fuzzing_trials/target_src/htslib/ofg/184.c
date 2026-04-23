#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_184(const uint8_t *data, size_t size) {
    sam_hdr_t *header = NULL;
    char *header_data = NULL;

    // Ensure size is non-zero and data is not NULL
    if (size == 0 || data == NULL) {
        return 0;
    }

    // Allocate memory for header data and copy input data
    header_data = (char *)malloc(size + 1);
    if (header_data == NULL) {
        return 0;
    }
    memcpy(header_data, data, size);
    header_data[size] = '\0'; // Null-terminate the string

    // Create a SAM header from the input data
    header = sam_hdr_parse(size, header_data);
    if (header == NULL) {
        free(header_data);
        return 0;
    }

    // Call the function-under-test
    const char *result = sam_hdr_str(header);

    // Clean up
    sam_hdr_destroy(header);
    free(header_data);

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

    LLVMFuzzerTestOneInput_184(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
