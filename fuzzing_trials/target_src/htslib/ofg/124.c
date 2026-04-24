#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to create meaningful strings
    if (size < 4) {
        return 0;
    }

    // Allocate and initialize a sam_hdr_t structure
    sam_hdr_t *hdr = sam_hdr_init();
    if (!hdr) {
        return 0;
    }

    // Create non-NULL strings from the input data
    char *str1 = (char *)malloc(size + 1);
    char *str2 = (char *)malloc(size + 1);
    char *str3 = (char *)malloc(size + 1);

    if (!str1 || !str2 || !str3) {
        free(str1);
        free(str2);
        free(str3);
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Copy data into strings and null-terminate them
    memcpy(str1, data, size);
    str1[size] = '\0';
    memcpy(str2, data, size);
    str2[size] = '\0';
    memcpy(str3, data, size);
    str3[size] = '\0';

    // Call the function-under-test
    sam_hdr_remove_line_id(hdr, str1, str2, str3);

    // Clean up
    free(str1);
    free(str2);
    free(str3);
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

    LLVMFuzzerTestOneInput_124(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
