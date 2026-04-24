#include <sys/stat.h>
#include "htslib/hts.h"
#include "htslib/sam.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For close() and unlink()

int LLVMFuzzerTestOneInput_107(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for creating necessary structures
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to simulate an htsFile
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }

    // Write the fuzz data to the temporary file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file as an htsFile
    htsFile *hts_file = hts_open(tmpl, "r");
    if (!hts_file) {
        unlink(tmpl);
        return 0;
    }

    // Read the header
    bam_hdr_t *header = sam_hdr_read(hts_file);
    if (!header) {
        hts_close(hts_file);
        unlink(tmpl);
        return 0;
    }

    // Initialize a BAM record
    bam1_t *b = bam_init1();
    if (!b) {
        bam_hdr_destroy(header);
        hts_close(hts_file);
        unlink(tmpl);
        return 0;
    }

    // Read a record from the file
    int result = sam_read1(hts_file, header, b);

    // Clean up
    bam_destroy1(b);
    bam_hdr_destroy(header);
    hts_close(hts_file);
    unlink(tmpl);

    return result;
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

    LLVMFuzzerTestOneInput_107(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
