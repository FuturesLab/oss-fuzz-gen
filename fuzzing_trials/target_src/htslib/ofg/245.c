#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_245(const uint8_t *data, size_t size) {
    // Call the function-under-test
    sam_hdr_t *header = sam_hdr_init();

    // Check if the header was successfully initialized
    if (header != NULL) {
        // Do something with the header if needed
        // For example, print a message indicating success
        printf("Header initialized successfully.\n");

        // Free the header when done
        sam_hdr_destroy(header);
    } else {
        // Handle the case where the header initialization failed
        printf("Failed to initialize header.\n");
    }

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

    LLVMFuzzerTestOneInput_245(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
