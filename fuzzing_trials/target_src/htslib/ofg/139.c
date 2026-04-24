#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0;
    }

    // Create a sam_hdr_t object
    sam_hdr_t *hdr = sam_hdr_init();
    if (!hdr) {
        return 0;
    }

    // Use the data to add a line to the header
    char *line = (char *)malloc(size + 1);
    if (!line) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(line, data, size);
    line[size] = '\0';

    // Add the line to the header
    if (sam_hdr_add_lines(hdr, line, 0) < 0) {
        free(line);
        sam_hdr_destroy(hdr);
        return 0;
    }
    free(line);

    // Extract an integer from the input data
    int tid = *((int *)data);

    // Call the function-under-test
    hts_pos_t length = sam_hdr_tid2len(hdr, tid);

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

    LLVMFuzzerTestOneInput_139(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
