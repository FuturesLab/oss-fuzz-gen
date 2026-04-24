#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h" // Correct path for sam_hdr_t and sam_hdr_str

int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    // Create a sam_hdr_t object
    sam_hdr_t *header = sam_hdr_init();

    // Ensure header is not NULL
    if (header == NULL) {
        return 0;
    }

    // Check if the input data is null-terminated before passing it to sam_hdr_add_lines
    // Allocate a new buffer with an extra byte for the null terminator
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        sam_hdr_destroy(header);
        return 0;
    }

    // Copy the input data into the new buffer and add a null terminator
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Initialize the header with the null-terminated data
    if (sam_hdr_add_lines(header, null_terminated_data, size) < 0) {
        free(null_terminated_data);
        sam_hdr_destroy(header);
        return 0;
    }

    // Free the allocated buffer
    free(null_terminated_data);

    // Call the function-under-test
    const char *result = sam_hdr_str(header);

    // Use the result in some way to prevent optimization out
    if (result != NULL) {
        volatile char c = result[0];
        (void)c;
    }

    // Clean up
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_146(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
