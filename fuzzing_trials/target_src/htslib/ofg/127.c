#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Assuming sam_hdr_t is defined in an included library
#include "htslib/sam.h"

// Fuzzing harness for sam_hdr_add_lines
int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to create a non-empty string
    if (size == 0) {
        return 0;
    }

    // Initialize sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Copy data to a null-terminated string
    char *lines = (char *)malloc(size + 1);
    if (lines == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(lines, data, size);
    lines[size] = '\0';

    // Call the function-under-test
    sam_hdr_add_lines(hdr, lines, size);

    // Clean up
    free(lines);
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

    LLVMFuzzerTestOneInput_127(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
