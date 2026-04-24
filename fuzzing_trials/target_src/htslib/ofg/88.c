#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include for memcpy
#include "/src/htslib/htslib/sam.h"  // Correct path to sam.h

int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    // Initialize the parameters for sam_hdr_remove_lines
    sam_hdr_t *hdr = sam_hdr_init();  // Assuming sam_hdr_init initializes a sam_hdr_t object
    if (hdr == NULL) {
        return 0;  // Exit if initialization fails
    }
    
    const char *type = "HD";  // Example type, can be varied
    const char *key = "VN";   // Example key, can be varied

    // Ensure the input data is not null and has sufficient size
    if (size < 1) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Use a valid value from the input data
    char val[256];
    size_t val_size = size < sizeof(val) ? size : sizeof(val) - 1;
    memcpy(val, data, val_size);
    val[val_size] = '\0';  // Null-terminate the string

    // Call the function-under-test
    int result = sam_hdr_remove_lines(hdr, type, key, val);

    // Clean up
    sam_hdr_destroy(hdr);  // Assuming sam_hdr_destroy frees the sam_hdr_t object

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

    LLVMFuzzerTestOneInput_88(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
