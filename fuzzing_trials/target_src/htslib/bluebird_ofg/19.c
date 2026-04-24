#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "htslib/sam.h"
#include "/src/htslib/htslib/bgzf.h"

int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    // Check if the size is sufficient for creating a bam1_t structure
    if (size < sizeof(bam1_t)) {
        return 0;
    }

    // Allocate memory for BGZF and bam1_t structures
    BGZF *bgzf = bgzf_open("/dev/null", "w");
    if (bgzf == NULL) {
        return 0;
    }

    bam1_t *bam_record = bam_init1();
    if (bam_record == NULL) {
        bgzf_close(bgzf);
        return 0;
    }

    // Copy the input data into bam_record's data field
    bam_record->data = (uint8_t *)malloc(size);
    if (bam_record->data == NULL) {
        bam_destroy1(bam_record);
        bgzf_close(bgzf);
        return 0;
    }
    memcpy(bam_record->data, data, size);
    bam_record->l_data = size;

    // Call the function-under-test
    bam_write1(bgzf, bam_record);

    // Clean up
    free(bam_record->data);
    bam_record->data = NULL; // Set to NULL to prevent double-free
    bam_destroy1(bam_record);
    bgzf_close(bgzf);

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

    LLVMFuzzerTestOneInput_19(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
