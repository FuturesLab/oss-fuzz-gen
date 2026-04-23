#include <stdint.h>
#include <stddef.h>
#include <htslib/sam.h>
#include <htslib/hts.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include this for mkstemp, write, close, and unlink functions

int LLVMFuzzerTestOneInput_288(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate the htsFile input
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) == -1) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file as an htsFile
    htsFile *hts_fp = hts_open(tmpl, "r");
    if (hts_fp == NULL) {
        return 0;
    }

    // Initialize a sam_hdr_t object
    sam_hdr_t *sam_hdr = sam_hdr_init();
    if (sam_hdr == NULL) {
        hts_close(hts_fp);
        return 0;
    }

    // Initialize a non-zero integer for the third parameter
    int some_int = 1;

    // Use a non-NULL string for the fourth parameter
    const char *some_string = "test_string";

    // Call the function-under-test
    sam_idx_init(hts_fp, sam_hdr, some_int, some_string);

    // Clean up
    sam_hdr_destroy(sam_hdr);
    hts_close(hts_fp);
    unlink(tmpl);

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

    LLVMFuzzerTestOneInput_288(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
