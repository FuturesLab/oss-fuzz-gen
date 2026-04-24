#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <htslib/sam.h>
#include <htslib/kstring.h>

int LLVMFuzzerTestOneInput_267(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to extract multiple strings
    if (size < 5) {
        return 0;
    }

    // Initialize sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();

    // Create and initialize kstring_t
    kstring_t ks;
    ks.l = 0;
    ks.m = size;
    ks.s = (char *)malloc(size);
    if (ks.s == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Copy data into kstring_t
    memcpy(ks.s, data, size);

    // Extract strings from the data
    const char *str1 = (const char *)data;
    const char *str2 = (const char *)(data + 1);
    const char *str3 = (const char *)(data + 2);
    const char *str4 = (const char *)(data + 3);

    // Call the function-under-test
    int result = sam_hdr_find_tag_id(hdr, str1, str2, str3, str4, &ks);

    // Clean up
    free(ks.s);
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

    LLVMFuzzerTestOneInput_267(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
