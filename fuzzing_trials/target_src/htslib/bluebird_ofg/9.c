#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "htslib/hts.h"
#include "htslib/sam.h"  // Include the SAM/BAM specific library

extern int sam_idx_save(htsFile *file);

int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzzing data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file as an htsFile in read mode
    htsFile *file = hts_open(tmpl, "r");
    if (file == NULL) {
        remove(tmpl);
        return 0;
    }

    // Read the header to ensure the file is a valid SAM/BAM/CRAM file
    sam_hdr_t *header = sam_hdr_read(file);
    if (header == NULL) {
        hts_close(file);
        remove(tmpl);
        return 0;
    }

    // Close and reopen the file in write mode to test sam_idx_save
    hts_close(file);
    file = hts_open(tmpl, "w");
    if (file == NULL) {
        sam_hdr_destroy(header);
        remove(tmpl);
        return 0;
    }

    // Write the header back to the file to simulate a valid SAM/BAM/CRAM file
    if (sam_hdr_write(file, header) < 0) {
        sam_hdr_destroy(header);
        hts_close(file);
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    sam_idx_save(file);

    // Close the htsFile and destroy the header
    hts_close(file);
    sam_hdr_destroy(header);

    // Remove the temporary file
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_9(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
