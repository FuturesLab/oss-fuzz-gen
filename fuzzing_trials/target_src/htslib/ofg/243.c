#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Assuming sam_hdr_t is a structure, define it for this example.
typedef struct {
    char *header_data;
    size_t length;
} sam_hdr_t;

// Function-under-test
size_t sam_hdr_length(sam_hdr_t *hdr);

// Fuzzing harness
int LLVMFuzzerTestOneInput_243(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a meaningful sam_hdr_t object
    if (size < sizeof(sam_hdr_t)) {
        return 0;
    }

    // Initialize sam_hdr_t structure
    sam_hdr_t hdr;
    hdr.header_data = (char *)malloc(size + 1); // +1 for null-terminator
    if (hdr.header_data == NULL) {
        return 0;
    }

    // Copy data into header_data and null-terminate
    memcpy(hdr.header_data, data, size);
    hdr.header_data[size] = '\0';
    hdr.length = size;

    // Call the function-under-test
    size_t length = sam_hdr_length(&hdr);

    // Clean up
    free(hdr.header_data);

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

    LLVMFuzzerTestOneInput_243(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
