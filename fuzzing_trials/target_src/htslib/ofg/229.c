#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_229(const uint8_t *data, size_t size) {
    // Allocate memory for sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();

    // Ensure hdr is not NULL
    if (hdr == NULL) {
        return 0;
    }

    // Initialize the sam_hdr_t with some data if possible
    // Here we are assuming the data is in SAM header format
    if (size > 0) {
        // Copy data into a temporary buffer and null-terminate it
        char *buffer = (char *)malloc(size + 1);
        if (buffer == NULL) {
            sam_hdr_destroy(hdr);
            return 0;
        }
        memcpy(buffer, data, size);
        buffer[size] = '\0';

        // Parse the buffer into the sam_hdr_t structure
        sam_hdr_t *parsed_hdr = sam_hdr_parse(size, buffer);
        if (parsed_hdr == NULL) {
            free(buffer);
            sam_hdr_destroy(hdr);
            return 0;
        }
        free(buffer);

        // Replace the original hdr with the parsed one
        sam_hdr_destroy(hdr);
        hdr = parsed_hdr;
    }

    // Call the function-under-test
    sam_hdr_t *dup_hdr = sam_hdr_dup(hdr);

    // Clean up
    sam_hdr_destroy(hdr);
    if (dup_hdr != NULL) {
        sam_hdr_destroy(dup_hdr);
    }

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

    LLVMFuzzerTestOneInput_229(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
