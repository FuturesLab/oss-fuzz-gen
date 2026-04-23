#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // Include for memcpy

// Assuming sam_hdr_t is defined somewhere in the included headers
typedef struct {
    // Placeholder for actual structure members
    int dummy;
} sam_hdr_t;

// Placeholder for the actual function definition
size_t sam_hdr_length(sam_hdr_t *hdr);

int LLVMFuzzerTestOneInput_242(const uint8_t *data, size_t size) {
    if (size < sizeof(sam_hdr_t)) {
        return 0; // Not enough data to create a sam_hdr_t
    }

    // Allocate memory for sam_hdr_t and copy data into it
    sam_hdr_t *hdr = (sam_hdr_t *)malloc(sizeof(sam_hdr_t));
    if (hdr == NULL) {
        return 0; // Allocation failed
    }

    // Initialize the sam_hdr_t structure with fuzz data
    // Assuming the structure can be initialized with raw data
    memcpy(hdr, data, sizeof(sam_hdr_t));

    // Call the function-under-test
    size_t length = sam_hdr_length(hdr);

    // Print the result (optional, for debugging purposes)
    printf("Header length: %zu\n", length);

    // Free allocated memory
    free(hdr);

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

    LLVMFuzzerTestOneInput_242(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
