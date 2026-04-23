#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/htslib/htslib/sam.h" // Correct path for sam_hdr_t

int LLVMFuzzerTestOneInput_248(const uint8_t *data, size_t size) {
    sam_hdr_t *hdr;
    char *arg1, *arg2, *arg3;
    void *arg4 = (void *)1; // Using a non-NULL value for the void argument

    // Initialize the sam_hdr_t object
    hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Ensure there is enough data for the string arguments
    if (size < 3) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Allocate and copy strings from the input data
    arg1 = (char *)malloc(size / 3 + 1);
    arg2 = (char *)malloc(size / 3 + 1);
    arg3 = (char *)malloc(size / 3 + 1);

    if (arg1 == NULL || arg2 == NULL || arg3 == NULL) {
        free(arg1);
        free(arg2);
        free(arg3);
        sam_hdr_destroy(hdr);
        return 0;
    }

    memcpy(arg1, data, size / 3);
    arg1[size / 3] = '\0';

    memcpy(arg2, data + size / 3, size / 3);
    arg2[size / 3] = '\0';

    memcpy(arg3, data + 2 * (size / 3), size / 3);
    arg3[size / 3] = '\0';

    // Call the function-under-test
    sam_hdr_update_line(hdr, arg1, arg2, arg3, arg4);

    // Clean up
    free(arg1);
    free(arg2);
    free(arg3);
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

    LLVMFuzzerTestOneInput_248(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
