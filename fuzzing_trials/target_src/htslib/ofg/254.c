#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"  // Assuming the sam_hdr_t type is defined in this header

int LLVMFuzzerTestOneInput_254(const uint8_t *data, size_t size) {
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated for use as a string
    char *name = (char *)malloc(size + 1);
    if (name == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(name, data, size);
    name[size] = '\0';

    // Call the function-under-test
    int result = sam_hdr_name2tid(hdr, name);

    // Clean up
    free(name);
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

    LLVMFuzzerTestOneInput_254(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
