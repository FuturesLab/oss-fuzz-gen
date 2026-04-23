#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // Include for memcpy
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_263(const uint8_t *data, size_t size) {
    // Create a buffer for header data
    char *header_data = (char *)malloc(size + 1);
    if (header_data == NULL) {
        return 0;
    }

    // Copy data into the header buffer and null-terminate it
    memcpy(header_data, data, size);
    header_data[size] = '\0';

    // Attempt to parse the header data
    sam_hdr_t *hdr = sam_hdr_parse(size, header_data);

    // Check if parsing was successful
    if (hdr == NULL) {
        // If parsing fails, clean up and return
        free(header_data);
        return 0;
    }

    // Clean up
    free(header_data);
    sam_hdr_destroy(hdr);

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

    LLVMFuzzerTestOneInput_263(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
