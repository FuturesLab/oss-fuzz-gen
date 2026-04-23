#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_244(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient to create a header
    if (size == 0) {
        return 0;
    }

    // Create a string from the input data
    char *header_text = (char *)malloc(size + 1);
    if (!header_text) {
        return 0;
    }
    memcpy(header_text, data, size);
    header_text[size] = '\0'; // Null-terminate the string

    // Call the function-under-test with the fuzzer's input
    sam_hdr_t *header = sam_hdr_parse(size, header_text);

    // Check if header is successfully initialized
    if (header != NULL) {
        // Perform additional operations with the header if needed
        // For example, you can print or manipulate the header

        // Clean up
        sam_hdr_destroy(header);
    }

    // Free the allocated memory
    free(header_text);

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

    LLVMFuzzerTestOneInput_244(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
