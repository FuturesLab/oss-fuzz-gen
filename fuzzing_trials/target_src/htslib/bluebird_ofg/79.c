#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"
#include "/src/htslib/htslib/kstring.h"  // Include for kstring_t

int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    // Ensure we have enough data to work with
    if (size < sizeof(bam_hdr_t) + sizeof(bam1_t)) {
        return 0;
    }

    // Initialize the bam_hdr_t structure
    bam_hdr_t *header = (bam_hdr_t *)malloc(sizeof(bam_hdr_t));
    if (!header) {
        return 0;
    }
    header->l_text = 1; // Assign a non-zero value
    header->text = (char *)malloc(header->l_text);
    if (!header->text) {
        free(header);
        return 0;
    }
    header->text[0] = '\0'; // Initialize with an empty string

    // Initialize the bam1_t structure
    bam1_t *alignment = bam_init1();
    if (!alignment) {
        free(header->text);
        free(header);
        return 0;
    }
    alignment->data = (uint8_t *)malloc(size - sizeof(bam_hdr_t));
    if (!alignment->data) {
        bam_destroy1(alignment);
        free(header->text);
        free(header);
        return 0;
    }
    alignment->l_data = size - sizeof(bam_hdr_t);
    memcpy(alignment->data, data + sizeof(bam_hdr_t), alignment->l_data);

    // Initialize the kstring_t structure
    kstring_t str;
    str.l = 0;
    str.m = 100; // Initial buffer size
    str.s = (char *)malloc(str.m);
    if (!str.s) {
        free(alignment->data); // Remove this line
        bam_destroy1(alignment);
        free(header->text);
        free(header);
        return 0;
    }

    // Call the function-under-test
    int ret = sam_format1(header, alignment, &str);

    // Check for errors in sam_format1
    if (ret < 0) {
        // Handle the error if needed
    }

    // Clean up
    free(str.s);
    bam_destroy1(alignment); // This will free alignment->data
    free(header->text);
    free(header);

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

    LLVMFuzzerTestOneInput_79(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
