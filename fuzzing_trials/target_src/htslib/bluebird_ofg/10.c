#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "htslib/sam.h"
#include "/src/htslib/htslib/bgzf.h" // Include the necessary header for BGZF operations
#include <unistd.h> // Include for mkstemp

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    // Check if size is sufficient to create a valid BAM file
    if (size < sizeof(bam1_t)) {
        return 0;
    }

    // Create a temporary file to simulate a BGZF stream
    char tmp_filename[] = "/tmp/fuzz_bam_XXXXXX";
    int tmp_fd = mkstemp(tmp_filename);
    if (tmp_fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(tmp_fd, data, size) != size) {
        close(tmp_fd);
        unlink(tmp_filename);
        return 0;
    }

    // Open the temporary file as a BGZF stream
    BGZF *bgzf = bgzf_open(tmp_filename, "r");
    if (bgzf == NULL) {
        close(tmp_fd);
        unlink(tmp_filename);
        return 0;
    }

    // Initialize the BAM file structure
    bam_hdr_t *header = bam_hdr_read(bgzf);
    if (header == NULL) {
        bgzf_close(bgzf);
        close(tmp_fd);
        unlink(tmp_filename);
        return 0;
    }

    bam1_t *b = bam_init1();
    if (b == NULL) {
        bam_hdr_destroy(header);
        bgzf_close(bgzf);
        close(tmp_fd);
        unlink(tmp_filename);
        return 0;
    }

    // Declare and initialize variables
    bam_plp_t pileup;
    int tid = 0;
    int pos = 0;
    int n_plp = 0;

    // Initialize the pileup with a dummy function and data
    pileup = bam_plp_init(NULL, NULL);

    // Check if pileup initialization was successful
    if (pileup == NULL) {
        bam_destroy1(b);
        bam_hdr_destroy(header);
        bgzf_close(bgzf);
        close(tmp_fd);
        unlink(tmp_filename);
        return 0;
    }

    // Read BAM records and feed them to the pileup
    while (bam_read1(bgzf, b) >= 0) {
        bam_plp_push(pileup, b);
    }

    // Call the function-under-test
    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function bam_plp_auto with bam_plp_next
    const bam_pileup1_t *result = bam_plp_next(pileup, &tid, &pos, &n_plp);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR

    // Clean up
    bam_plp_destroy(pileup);
    bam_destroy1(b);
    bam_hdr_destroy(header);
    bgzf_close(bgzf);
    close(tmp_fd);
    unlink(tmp_filename);

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

    LLVMFuzzerTestOneInput_10(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
