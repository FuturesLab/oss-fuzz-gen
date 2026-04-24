#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <htslib/sam.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_165(const uint8_t *data, size_t size) {
    // Initialize necessary variables
    sam_hdr_t *header = sam_hdr_init();
    char **regions = (char **)malloc(sizeof(char *) * 2);
    unsigned int n = 2;

    // Ensure data is large enough to be used for the regions
    if (size < 2) {
        sam_hdr_destroy(header);
        free(regions);
        return 0;
    }

    // Allocate memory for region strings and copy data into them
    regions[0] = (char *)malloc((size / 2) + 1);
    regions[1] = (char *)malloc((size / 2) + 1);
    memcpy(regions[0], data, size / 2);
    memcpy(regions[1], data + (size / 2), size / 2);
    regions[0][size / 2] = '\0';
    regions[1][size / 2] = '\0';

    // Call the function-under-test
    // Note: We cannot create a valid hts_idx_t without using an appropriate library function
    // so the call to sam_itr_regarray is for demonstration purposes only.
    hts_itr_t *itr = sam_itr_regarray(NULL, header, regions, n);

    // Clean up
    if (itr != NULL) {
        hts_itr_destroy(itr);
    }
    sam_hdr_destroy(header);
    free(regions[0]);
    free(regions[1]);
    free(regions);

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

    LLVMFuzzerTestOneInput_165(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
