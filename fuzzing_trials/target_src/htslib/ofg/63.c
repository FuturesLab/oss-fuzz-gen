#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    // Initialize a samFile pointer
    samFile *file = sam_open("/dev/null", "w"); // Open a dummy file for writing

    // Use the data to create a header text, ensuring it's null-terminated
    char *header_text = (char *)malloc(size + 1);
    if (header_text == NULL) {
        sam_close(file);
        return 0;
    }
    memcpy(header_text, data, size);
    header_text[size] = '\0';

    // Parse the header text into the sam_hdr_t structure
    sam_hdr_t *header = sam_hdr_parse(size, header_text);
    if (header == NULL) {
        free(header_text);
        sam_close(file);
        return 0;
    }

    // Set some options
    int options = 0; // You can vary this to test different options

    // Call the function-under-test
    sam_hdr_set(file, header, options);

    // Clean up
    free(header_text);
    sam_hdr_destroy(header);
    sam_close(file);

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

    LLVMFuzzerTestOneInput_63(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
