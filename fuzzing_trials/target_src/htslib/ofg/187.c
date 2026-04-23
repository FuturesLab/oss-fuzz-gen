#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "htslib/sam.h" // Assuming the sam_hdr_t type is defined here

int LLVMFuzzerTestOneInput_187(const uint8_t *data, size_t size) {
    // Initialize sam_hdr_t object
    sam_hdr_t *hdr = sam_hdr_init();

    // Ensure non-null data for the second parameter
    const char *line_type = "HD"; // Example line type, assuming "HD" is a valid line type

    // Ensure a valid index for the third parameter
    int index = 0; // Start with index 0

    // Call the function-under-test
    const char *result = sam_hdr_line_name(hdr, line_type, index);

    // Use the result in some way to avoid compiler optimizations removing the call
    if (result != NULL) {
        printf("Line name: %s\n", result);
    }

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

    LLVMFuzzerTestOneInput_187(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
