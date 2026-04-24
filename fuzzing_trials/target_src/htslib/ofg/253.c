#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <htslib/sam.h> // Correct path for sam_hdr_t and sam_hdr_name2tid

int LLVMFuzzerTestOneInput_253(const uint8_t *data, size_t size) {
    // Initialize sam_hdr_t structure
    sam_hdr_t *header = sam_hdr_init();
    if (header == NULL) {
        return 0; // Return if initialization fails
    }

    // Add a dummy header line to the sam_hdr_t structure
    const char *dummy_header_line = "@SQ\tSN:chr1\tLN:248956422";
    if (sam_hdr_add_lines(header, dummy_header_line, strlen(dummy_header_line)) < 0) {
        sam_hdr_destroy(header);
        return 0; // Return if adding header line fails
    }

    // Ensure there's at least one byte for the string
    if (size == 0) {
        sam_hdr_destroy(header);
        return 0;
    }

    // Allocate memory for the string and ensure null-termination
    char *name = (char *)malloc(size + 1);
    if (name == NULL) {
        sam_hdr_destroy(header);
        return 0; // Return if allocation fails
    }
    memcpy(name, data, size);
    name[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    int result = sam_hdr_name2tid(header, name);

    // Clean up
    free(name);
    sam_hdr_destroy(header);

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

    LLVMFuzzerTestOneInput_253(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
