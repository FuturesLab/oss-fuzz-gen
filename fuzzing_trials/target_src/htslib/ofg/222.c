#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>
#include <htslib/kstring.h>

int LLVMFuzzerTestOneInput_222(const uint8_t *data, size_t size) {
    // Ensure there's enough data for all parameters
    if (size < 4) return 0;

    // Initialize sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();

    // Split the input data into parts for each parameter
    size_t part_size = size / 4;
    const char *str1 = (const char *)data;
    const char *str2 = (const char *)(data + part_size);
    const char *str3 = (const char *)(data + 2 * part_size);
    const char *str4 = (const char *)(data + 3 * part_size);

    // Initialize kstring_t
    kstring_t ks;
    ks.l = 0;
    ks.m = 0;
    ks.s = NULL;

    // Ensure strings are null-terminated
    char *str1_nt = strndup(str1, part_size);
    char *str2_nt = strndup(str2, part_size);
    char *str3_nt = strndup(str3, part_size);
    char *str4_nt = strndup(str4, part_size);

    // Call the function-under-test
    sam_hdr_find_line_id(hdr, str1_nt, str2_nt, str3_nt, &ks);

    // Clean up
    free(str1_nt);
    free(str2_nt);
    free(str3_nt);
    free(str4_nt);
    sam_hdr_destroy(hdr);
    free(ks.s);

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

    LLVMFuzzerTestOneInput_222(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
