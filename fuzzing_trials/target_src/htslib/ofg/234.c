#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // For close() and unlink()
#include <fcntl.h>  // For mkstemp()
#include <htslib/hts.h>
#include <htslib/hts_defs.h>
#include <htslib/vcf.h>     // Include for VCF-related functions
#include "/src/htslib/htslib/vcf.h" // Correct path for hts_idx_seqnames

int LLVMFuzzerTestOneInput_234(const uint8_t *data, size_t size) {
    // Initialize necessary variables
    hts_idx_t *index = NULL;
    int num_seqnames = 0;
    hts_id2name_f id2name_func = NULL;
    void *id2name_data = NULL;

    // Create a temporary file to simulate an index file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl); // Use unlink instead of remove for POSIX compliance
        return 0;
    }
    close(fd);

    // Open the index file
    index = hts_idx_load(tmpl, HTS_FMT_BAI);
    if (index == NULL) {
        // Clean up the temporary file
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    const char **seqnames = hts_idx_seqnames(index, &num_seqnames, id2name_func, id2name_data);

    // Clean up
    if (seqnames != NULL) {
        for (int i = 0; i < num_seqnames; i++) {
            free((void *)seqnames[i]);
        }
        free(seqnames);
    }
    hts_idx_destroy(index);
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

    LLVMFuzzerTestOneInput_234(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
