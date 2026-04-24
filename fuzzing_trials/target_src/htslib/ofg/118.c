#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <htslib/sam.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file as an htsFile
    htsFile *hts_file = hts_open(tmpl, "r");
    if (hts_file == NULL) {
        return 0;
    }

    // Initialize sam_hdr_t and bam1_t
    sam_hdr_t *header = sam_hdr_read(hts_file);
    if (header == NULL) {
        hts_close(hts_file);
        return 0;
    }

    bam1_t *b = bam_init1();
    if (b == NULL) {
        sam_hdr_destroy(header);
        hts_close(hts_file);
        return 0;
    }

    // Call the function-under-test
    sam_read1(hts_file, header, b);

    // Clean up
    bam_destroy1(b);
    sam_hdr_destroy(header);
    hts_close(hts_file);
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

    LLVMFuzzerTestOneInput_118(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
