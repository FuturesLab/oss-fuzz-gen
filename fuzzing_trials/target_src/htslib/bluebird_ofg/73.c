#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "htslib/sam.h"  // Assuming the function is part of the htslib library

int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
    if (size < 5) return 0; // Ensure there's enough data for non-NULL inputs

    // Initialize sam_hdr_t object
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) return 0;

    // Allocate memory for kstring_t
    kstring_t ks;
    ks.l = 0;
    ks.m = size;
    ks.s = (char *)malloc(size + 1);
    if (ks.s == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Use the first part of data for the tag
    const char *tag = (const char *)data;
    size_t tag_len = strnlen(tag, size);
    if (tag_len == size) {
        free(ks.s);
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Use the second part of data for the type
    const char *type = (const char *)(data + tag_len + 1);
    size_t type_len = strnlen(type, size - tag_len - 1);
    if (tag_len + type_len + 1 >= size) {
        free(ks.s);
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Use the remaining data as an integer
    int pos = (int)data[tag_len + type_len + 2];

    // Call the function-under-test
    sam_hdr_find_tag_pos(hdr, tag, pos, type, &ks);

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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_73(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
