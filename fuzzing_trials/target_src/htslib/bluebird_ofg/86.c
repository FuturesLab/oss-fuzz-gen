#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"  // Assuming sam_hdr_t is defined in this header

int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated for string operations
    char *input_str = (char *)malloc(size + 1);
    if (input_str == NULL) {
        return 0;
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';

    // Parse the input string into a new header
    sam_hdr_t *hdr = sam_hdr_parse(size, input_str);
    if (hdr == NULL) {
        free(input_str);
        return 0;
    }

    // Check if the input string is a valid header line
    if (sam_hdr_count_lines(hdr, "HD") == 0) {
        // If there are no header lines, clean up and return
        sam_hdr_destroy(hdr);
        free(input_str);
        return 0;
    }

    // Call the function-under-test
    int result = sam_hdr_count_lines(hdr, "SQ"); // Using "SQ" as a valid header type

    // Clean up
    free(input_str);
    sam_hdr_destroy(hdr);

    return result;
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

    LLVMFuzzerTestOneInput_86(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
