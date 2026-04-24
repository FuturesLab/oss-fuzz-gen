#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"

extern int sam_hdr_find_line_id(sam_hdr_t *, const char *, const char *, const char *, kstring_t *);

int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to split into parts
    if (size < 4) return 0;

    // Initialize sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) return 0;

    // Split data into parts for the function parameters
    size_t part_size = size / 4;
    const char *type = (const char *)data;
    const char *id = (const char *)(data + part_size);
    const char *val = (const char *)(data + 2 * part_size);
    const char *str = (const char *)(data + 3 * part_size);

    // Ensure null-termination for strings
    char *type_str = strndup(type, part_size);
    char *id_str = strndup(id, part_size);
    char *val_str = strndup(val, part_size);
    char *str_str = strndup(str, size - 3 * part_size);

    // Initialize kstring_t
    kstring_t ks;
    ks.l = 0;
    ks.m = 0;
    ks.s = NULL;

    // Call the function-under-test
    int result = sam_hdr_find_line_id(hdr, type_str, id_str, val_str, &ks);

    // Clean up
    free(type_str);
    free(id_str);
    free(val_str);
    free(str_str);
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

    LLVMFuzzerTestOneInput_74(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
