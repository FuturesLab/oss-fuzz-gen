#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    // Initialize variables
    sam_hdr_t *header = sam_hdr_init();
    const char *region = (const char *)data;
    int tid = 0;
    hts_pos_t beg = 0;
    hts_pos_t end = 0;
    int flags = 0;

    // Ensure the region string is null-terminated
    char *region_copy = (char *)malloc(size + 1);
    if (region_copy == NULL) {
        sam_hdr_destroy(header);
        return 0;
    }
    memcpy(region_copy, data, size);
    region_copy[size] = '\0';

    // Call the function-under-test
    const char *result = sam_parse_region(header, region_copy, &tid, &beg, &end, flags);

    // Clean up
    free(region_copy);
    sam_hdr_destroy(header);

    return 0;
}

#ifdef __cplusplus
}
#endif
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

    LLVMFuzzerTestOneInput_46(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
