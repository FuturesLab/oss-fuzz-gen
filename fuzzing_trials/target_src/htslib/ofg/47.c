#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for meaningful input
    if (size < 10) {
        return 0;
    }

    // Allocate and initialize sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();
    if (!hdr) {
        return 0;
    }

    // Create a null-terminated string for the region
    char *region = (char *)malloc(size + 1);
    if (!region) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(region, data, size);
    region[size] = '\0';

    // Initialize other parameters
    int tid = 0;
    hts_pos_t beg = 0;
    hts_pos_t end = 0;
    int flags = 0;  // You can vary this if needed

    // Call the function-under-test
    const char *result = sam_parse_region(hdr, region, &tid, &beg, &end, flags);

    // Clean up
    free(region);
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

    LLVMFuzzerTestOneInput_47(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
