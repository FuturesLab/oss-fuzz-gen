#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <htslib/sam.h> // Assuming sam_hdr_t is defined in the htslib library

int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Simulate filling the header with some data from the input
    // This is just a placeholder as actual header initialization would depend on the library's API
    if (size > 0) {
        // Use the data to modify the header in some way
        // This is a placeholder for actual logic to initialize the header
        hdr->n_targets = (int)data[0]; // Example modification
    }

    // Call the function-under-test
    sam_hdr_incr_ref(hdr);

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

    LLVMFuzzerTestOneInput_91(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
