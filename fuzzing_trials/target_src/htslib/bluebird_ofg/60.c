#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h> // For close() and remove()
#include "htslib/hts.h"
#include "htslib/sam.h" // For sam_idx_save()

int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate an htsFile
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Unable to create a temporary file, exit early
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0; // Unable to open file descriptor, exit early
    }

    // Write the fuzz data to the temporary file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file as an htsFile for writing
    htsFile *hts_file = hts_open(tmpl, "wb");
    if (!hts_file) {
        remove(tmpl); // Clean up the temporary file
        return 0; // Unable to open htsFile, exit early
    }

    // Attempt to write a header to the file to make it a valid SAM/BAM file
    bam_hdr_t *header = bam_hdr_init();
    if (header) {
        header->n_targets = 0; // No targets
        header->target_len = NULL;
        header->target_name = NULL;
        header->text = NULL;
        header->l_text = 0;

        // Write the header
        if (sam_hdr_write(hts_file, header) >= 0) {
            // Ensure the file is properly initialized for indexing
            int min_shift = 14; // Example value for min_shift
            const char *fnidx = "/tmp/fuzzfile.bai"; // Provide a valid index filename
            if (sam_idx_init(hts_file, header, min_shift, fnidx) >= 0) {
                // Call the function-under-test
                int result = sam_idx_save(hts_file);
                (void)result; // Suppress unused variable warning
            }
        }
        bam_hdr_destroy(header);
    }

    // Clean up
    hts_close(hts_file);
    remove(tmpl); // Remove the temporary file

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

    LLVMFuzzerTestOneInput_60(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
