#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Initialize sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Create a non-NULL string from the input data
    char *pg_id = (char *)malloc(size + 1);
    if (pg_id == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(pg_id, data, size);
    pg_id[size] = '\0'; // Ensure null-termination

    // Add a dummy program record to ensure hdr is not empty
    if (sam_hdr_add_pg(hdr, "ID", "dummy", "PN", "dummy_program", NULL) != 0) {
        free(pg_id);
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Call the function-under-test
    const char *result = sam_hdr_pg_id(hdr, pg_id);

    // Check the result to ensure the function is being tested
    if (result != NULL) {
        // Do something with result to ensure code coverage
    }

    // Clean up
    free(pg_id);
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

    LLVMFuzzerTestOneInput_20(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
