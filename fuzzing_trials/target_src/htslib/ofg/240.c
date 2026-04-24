#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h> // Ensure that the htslib library is included for sam_hdr_t

int LLVMFuzzerTestOneInput_240(const uint8_t *data, size_t size) {
    // Ensure size is non-zero and data is not NULL
    if (size == 0 || data == NULL) {
        return 0;
    }

    // Allocate memory for the header string
    char *header_str = (char *)malloc(size + 1);
    if (header_str == NULL) {
        return 0;
    }

    // Copy the data into header_str and null-terminate it
    memcpy(header_str, data, size);
    header_str[size] = '\0';

    // Call the function-under-test
    sam_hdr_t *header = sam_hdr_parse(size, header_str);

    // Clean up
    if (header != NULL) {
        sam_hdr_destroy(header);
    }
    free(header_str);

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

    LLVMFuzzerTestOneInput_240(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
