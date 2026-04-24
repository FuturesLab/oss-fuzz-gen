#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0; // Early exit if there's not enough data
    }

    // Initialize sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();
    if (!hdr) {
        return 0; // Exit if header initialization fails
    }

    // Allocate memory for the line string
    char *line = (char *)malloc(size + 1);
    if (!line) {
        sam_hdr_destroy(hdr);
        return 0; // Exit if memory allocation fails
    }

    // Copy data to line and null-terminate
    memcpy(line, data, size);
    line[size] = '\0';

    // Call the function-under-test
    sam_hdr_add_line(hdr, line, NULL);

    // Clean up
    free(line);
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

    LLVMFuzzerTestOneInput_111(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
