#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Check if size is sufficient to extract necessary components
    if (size < 3) {
        return 0;
    }

    // Initialize a sam_hdr_t object
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Use part of the data as a string for the second parameter
    // Ensure string is null-terminated
    size_t str_len = size - 2;
    char *str = (char *)malloc(str_len + 1);
    if (str == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(str, data, str_len);
    str[str_len] = '\0';

    // Use part of the data as an integer for the third parameter
    int pos = (int)data[size - 1];

    // Call the function-under-test
    sam_hdr_remove_line_pos(hdr, str, pos);

    // Clean up
    free(str);
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_40(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
