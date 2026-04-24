#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"

// Mock function to create a sample sam_hdr_t
sam_hdr_t *create_sample_sam_hdr() {
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return NULL;
    }

    // Add some sample target names to the header
    sam_hdr_add_line(hdr, "SQ", "SN:chr1", "LN:248956422", NULL);
    sam_hdr_add_line(hdr, "SQ", "SN:chr2", "LN:242193529", NULL);
    sam_hdr_add_line(hdr, "SQ", "SN:chr3", "LN:198295559", NULL);

    return hdr;
}

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0;
    }

    // Create a sample sam_hdr_t
    sam_hdr_t *hdr = create_sample_sam_hdr();
    if (hdr == NULL) {
        return 0;
    }

    // Use the first 4 bytes of data to form an integer index
    int index = *((int *)data);

    // Call the function-under-test
    const char *name = sam_hdr_tid2name(hdr, index);

    // Print the result for debugging purposes
    if (name != NULL) {
        printf("Index: %d, Name: %s\n", index, name);
    } else {
        printf("Index: %d, Name: NULL\n", index);
    }

    // Clean up
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_45(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
