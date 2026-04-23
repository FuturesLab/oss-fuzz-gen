#include <stdint.h>
#include <stddef.h>
#include <htslib/sam.h>
#include <htslib/hts.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include for close() and mkstemp()

int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    // Create a temporary file to use with htsFile
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        remove(tmpl);
        return 0;
    }

    // Close the file descriptor as hts_open will open it again
    close(fd);

    // Open the temporary file as an htsFile
    htsFile *file = hts_open(tmpl, "r");
    if (file == NULL) {
        remove(tmpl);
        return 0;
    }

    // Create a sam_hdr_t object
    sam_hdr_t *header = sam_hdr_init();
    if (header == NULL) {
        hts_close(file);
        remove(tmpl);
        return 0;
    }

    // Add a dummy header line to ensure header is not empty
    if (sam_hdr_add_line(header, "HD", "VN:1.0", NULL) != 0) {
        sam_hdr_destroy(header);
        hts_close(file);
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    sam_hdr_write(file, header);

    // Clean up
    sam_hdr_destroy(header);
    hts_close(file);
    remove(tmpl);

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

    LLVMFuzzerTestOneInput_85(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
