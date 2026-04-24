#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>
#include <htslib/hts.h>
#include <htslib/regidx.h>  // Include the necessary header for hts_reglist_t

int LLVMFuzzerTestOneInput_270(const uint8_t *data, size_t size) {
    // Initialize variables
    hts_idx_t *idx = NULL;  // Initialize idx to NULL since we cannot allocate it directly
    sam_hdr_t *hdr = sam_hdr_init();
    hts_reglist_t *reglist = (hts_reglist_t *)malloc(sizeof(hts_reglist_t));
    unsigned int flags = 0;

    // Ensure that the data is not empty
    if (size == 0 || !hdr || !reglist) {
        sam_hdr_destroy(hdr);
        free(reglist);
        return 0;
    }

    // Initialize hdr with some data
    sam_hdr_add_line(hdr, "HD", "VN", "1.0", NULL);

    // Initialize reglist with some data
    reglist->reg = (char *)malloc(size + 1);
    reglist->count = 1; // Set count to 1 to indicate there is one region
    reglist->intervals = (hts_pair_pos_t *)malloc(sizeof(hts_pair_pos_t) * reglist->count);
    if (reglist->reg && reglist->intervals) {
        memcpy((void *)reglist->reg, data, size); // Cast to void* to avoid const warning
        ((char *)reglist->reg)[size] = '\0'; // Cast to char* to modify the content
        // Initialize intervals with some data
        reglist->intervals[0].beg = 0;
        reglist->intervals[0].end = size > 1 ? (int)data[1] : 1; // Use some data for end
    }

    // Call the function-under-test
    hts_itr_t *itr = sam_itr_regions(idx, hdr, reglist, flags);

    // Clean up
    if (itr) hts_itr_destroy(itr);
    sam_hdr_destroy(hdr);
    free((void *)reglist->reg); // Cast to void* to avoid const warning
    free(reglist->intervals);
    free(reglist);

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

    LLVMFuzzerTestOneInput_270(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
