#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"  // Assuming this header provides the definition for sam_hdr_t and kstring_t

int LLVMFuzzerTestOneInput_78(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    sam_hdr_t *hdr = sam_hdr_init();
    const char *type = "type_example";
    const char *id = "id_example";
    const char *tag = "tag_example";
    const char *value = "value_example";
    kstring_t str = {0, 0, NULL};

    // Ensure that the header is not NULL
    if (hdr == NULL) {
        return 0;
    }

    // Call the function-under-test
    int result = sam_hdr_find_tag_id(hdr, type, id, tag, value, &str);

    // Clean up
    sam_hdr_destroy(hdr);
    free(str.s);

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

    LLVMFuzzerTestOneInput_78(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
