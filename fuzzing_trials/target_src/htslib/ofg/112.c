#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <htslib/sam.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
    // Create a temporary file to act as htsFile
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }

    // Open the temporary file as an htsFile
    htsFile *hts_file = hts_open(tmpl, "rb");
    if (hts_file == NULL) {
        close(fd);
        return 0;
    }

    // Initialize sam_hdr_t and bam1_t
    sam_hdr_t *sam_header = sam_hdr_init();
    bam1_t *bam_record = bam_init1();

    if (sam_header == NULL || bam_record == NULL) {
        hts_close(hts_file);
        close(fd);
        return 0;
    }

    // Call the function-under-test
    sam_write1(hts_file, sam_header, bam_record);

    // Clean up
    bam_destroy1(bam_record);
    sam_hdr_destroy(sam_header);
    hts_close(hts_file);
    close(fd);

    return 0;
}