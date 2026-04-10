#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_218(const uint8_t *data, size_t size) {
    sam_hdr_t *hdr = NULL;

    // Ensure size is valid for creating a string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *input_str = (char *)malloc(size + 1);
    if (input_str == NULL) {
        return 0;
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';

    // Create a header from the input string
    hdr = sam_hdr_parse(size, input_str);
    if (hdr == NULL) {
        free(input_str);
        return 0;
    }

    // Call the function-under-test
    const char *result = sam_hdr_str(hdr);

    // Clean up
    sam_hdr_destroy(hdr);
    free(input_str);

    return 0;
}