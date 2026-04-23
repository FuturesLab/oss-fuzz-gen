#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <htslib/sam.h>
#include <htslib/bgzf.h>

// Fuzzing harness for bam_hdr_write function
int LLVMFuzzerTestOneInput_262(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a BGZF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Open the temporary file as a BGZF file
    BGZF *bgzf = bgzf_fdopen(fd, "w");
    if (bgzf == NULL) {
        close(fd);
        return 0;
    }

    // Initialize a sam_hdr_t structure
    sam_hdr_t *header = sam_hdr_init();
    if (header == NULL) {
        bgzf_close(bgzf);
        return 0;
    }

    // Use the input data to populate the header
    // Assume the input data is a null-terminated string for simplicity
    if (size > 0) {
        char *header_data = (char *)malloc(size + 1);
        if (header_data == NULL) {
            sam_hdr_destroy(header);
            bgzf_close(bgzf);
            return 0;
        }
        memcpy(header_data, data, size);
        header_data[size] = '\0'; // Ensure null-termination

        // Attempt to parse the input data as SAM header lines
        if (sam_hdr_add_lines(header, header_data, size) < 0) {
            // If parsing fails, clean up and return
            free(header_data);
            sam_hdr_destroy(header);
            bgzf_close(bgzf);
            return 0;
        }

        free(header_data);
    }

    // Call the function-under-test
    bam_hdr_write(bgzf, header);

    // Clean up
    sam_hdr_destroy(header);
    bgzf_close(bgzf);
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

    LLVMFuzzerTestOneInput_262(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
