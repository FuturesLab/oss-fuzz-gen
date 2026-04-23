#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "htslib/sam.h"
#include "htslib/hts.h"

int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate an htsFile input
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
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file using hts_open
    htsFile *hts_fp = hts_open(tmpl, "r");
    if (!hts_fp) {
        remove(tmpl);
        return 0;
    }

    // Initialize sam_hdr_t and bam1_t structures
    sam_hdr_t *sam_hdr = sam_hdr_init();
    if (!sam_hdr) {
        hts_close(hts_fp);
        remove(tmpl);
        return 0;
    }

    bam1_t *bam_record = bam_init1();
    if (!bam_record) {
        sam_hdr_destroy(sam_hdr);
        hts_close(hts_fp);
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    int result = sam_read1(hts_fp, sam_hdr, bam_record);

    // Clean up
    bam_destroy1(bam_record);
    sam_hdr_destroy(sam_hdr);
    hts_close(hts_fp);
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

    LLVMFuzzerTestOneInput_42(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
