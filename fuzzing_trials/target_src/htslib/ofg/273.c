#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/htslib/htslib/sam.h" // Correct path for sam_hdr_t definition
#include "/src/htslib/htslib/hts.h" // Correct path for kstring_t definition

int LLVMFuzzerTestOneInput_273(const uint8_t *data, size_t size) {
    // Initialize sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0; // Exit if initialization fails
    }

    // Ensure the input data is not empty
    if (size == 0) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Create a null-terminated string from the input data
    char *str = (char *)malloc(size + 1);
    if (str == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(str, data, size);
    str[size] = '\0';

    // Initialize kstring_t
    kstring_t ks;
    ks.l = 0;
    ks.m = 0;
    ks.s = NULL;

    // Call the function under test with various positions
    for (int pos = 0; pos < 10; ++pos) {
        sam_hdr_find_line_pos(hdr, str, pos, &ks);
    }

    // Clean up
    free(str);
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

    LLVMFuzzerTestOneInput_273(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
