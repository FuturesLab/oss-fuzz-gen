#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <htslib/sam.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_287(const uint8_t *data, size_t size) {
    // Ensure there is enough data for the filename
    if (size < 5) {
        return 0;
    }

    // Create a temporary file to simulate an htsFile
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *fp = fdopen(fd, "wb");
    if (!fp) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, fp);
    fclose(fp);

    // Open the temporary file as an htsFile
    htsFile *hts_file = hts_open(tmpl, "r");
    if (!hts_file) {
        remove(tmpl);
        return 0;
    }

    // Create a dummy sam_hdr_t
    sam_hdr_t *sam_hdr = sam_hdr_init();
    if (!sam_hdr) {
        hts_close(hts_file);
        remove(tmpl);
        return 0;
    }

    // Use a non-zero integer for options
    int options = 1;

    // Use the filename as the string parameter
    const char *str_param = tmpl;

    // Call the function-under-test
    sam_idx_init(hts_file, sam_hdr, options, str_param);

    // Clean up
    sam_hdr_destroy(sam_hdr);
    hts_close(hts_file);
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

    LLVMFuzzerTestOneInput_287(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
