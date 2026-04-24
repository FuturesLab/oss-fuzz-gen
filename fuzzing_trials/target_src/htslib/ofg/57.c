#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    sam_hdr_t *hdr = NULL;

    if (size == 0) {
        return 0;
    }

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzz_sam_hdrXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Open the temporary file as a SAM file
    samFile *file = sam_open(tmpl, "r");
    if (file == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Read the header from the SAM file
    hdr = sam_hdr_read(file);
    if (hdr != NULL) {
        // Call the function under test
        int nref = sam_hdr_nref(hdr);
    }

    // Clean up
    if (hdr != NULL) {
        sam_hdr_destroy(hdr);
    }
    sam_close(file);
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

    LLVMFuzzerTestOneInput_57(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
