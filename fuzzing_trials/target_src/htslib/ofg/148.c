#include <stdint.h>
#include <stdlib.h>
#include <htslib/sam.h>
#include <htslib/hts.h>
#include <htslib/bgzf.h>

// Function to create a mock BAM header
bam_hdr_t* create_mock_bam_header() {
    bam_hdr_t *header = bam_hdr_init();
    header->n_targets = 1;
    header->target_len = (uint32_t*)malloc(sizeof(uint32_t));
    header->target_len[0] = 1000; // Arbitrary length
    header->target_name = (char**)malloc(sizeof(char*));
    header->target_name[0] = strdup("chr1");
    return header;
}

int LLVMFuzzerTestOneInput_148(const uint8_t *data, size_t size) {
    // Declare and initialize all necessary variables
    hts_idx_t *index = hts_idx_init(HTS_FMT_BAI, HTS_IDX_NONE, 0, 0, 0); // Properly initialize index
    int tid = 0; // Assuming a valid reference id
    hts_pos_t beg = 0; // Start position
    hts_pos_t end = 1000; // End position, arbitrary non-zero value

    // Check if the size is sufficient to map to the function parameters
    if (size < sizeof(int) + 2 * sizeof(hts_pos_t)) {
        hts_idx_destroy(index);
        return 0;
    }

    // Create a mock BAM header
    bam_hdr_t *header = create_mock_bam_header();

    // Call the function-under-test with a valid BAM header
    hts_itr_t *itr = sam_itr_queryi(index, tid, beg, end);

    // Clean up and free allocated memory
    if (itr != NULL) {
        hts_itr_destroy(itr);
    }
    hts_idx_destroy(index);
    bam_hdr_destroy(header);

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

    LLVMFuzzerTestOneInput_148(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
