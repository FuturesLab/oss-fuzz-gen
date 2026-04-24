#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_261(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    sam_hdr_t *hdr = sam_hdr_init();
    const char *type = "SQ";  // Assuming a common type, e.g., "SQ" for sequence
    int pos = 0;  // Start with position 0

    // Ensure hdr is not NULL
    if (hdr == NULL) {
        return 0;
    }

    // Add some dummy header lines to hdr for testing
    if (sam_hdr_add_line(hdr, type, "ID", "test", NULL) < 0) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Call the function-under-test
    int result = sam_hdr_remove_line_pos(hdr, type, pos);

    // Clean up
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

    LLVMFuzzerTestOneInput_261(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
