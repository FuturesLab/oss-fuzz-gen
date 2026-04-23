#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>
#include <htslib/kstring.h>

int LLVMFuzzerTestOneInput_292(const uint8_t *data, size_t size) {
    if (size < 5) {
        return 0; // Ensure there's enough data for the inputs
    }

    // Initialize sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Use part of the data as a string for the second parameter
    const char *str1 = (const char *)data;

    // Use the next byte as an integer for the third parameter
    int int_param = (int)data[size / 2];

    // Use another part of the data as a string for the fourth parameter
    const char *str2 = (const char *)(data + size / 2 + 1);

    // Initialize kstring_t
    kstring_t ks;
    ks.l = 0;
    ks.m = size - (size / 2 + 1);
    ks.s = (char *)malloc(ks.m);
    if (ks.s == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(ks.s, data + size / 2 + 1, ks.m);

    // Call the function-under-test
    sam_hdr_find_tag_pos(hdr, str1, int_param, str2, &ks);

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

    LLVMFuzzerTestOneInput_292(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
