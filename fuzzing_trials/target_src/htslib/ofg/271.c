#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <htslib/hts.h>
#include <htslib/hts_defs.h>
#include <htslib/hts_log.h>
#include <htslib/sam.h>
#include <htslib/tbx.h>
#include <htslib/vcf.h>
#include <htslib/vcfutils.h>
#include <htslib/kstring.h>
#include <htslib/kseq.h>
#include <htslib/khash.h>
#include <htslib/knetfile.h>
#include <htslib/khash_str2int.h>

int LLVMFuzzerTestOneInput_271(const uint8_t *data, size_t size) {
    char tmpl1[] = "/tmp/fuzzfileXXXXXX";
    char tmpl2[] = "/tmp/fuzzfileXXXXXX";
    int fd1 = mkstemp(tmpl1);
    int fd2 = mkstemp(tmpl2);

    if (fd1 == -1 || fd2 == -1) {
        if (fd1 != -1) close(fd1);
        if (fd2 != -1) close(fd2);
        return 0;
    }

    // Write data to the first temporary file
    if (write(fd1, data, size) != size) {
        close(fd1);
        close(fd2);
        return 0;
    }

    // Close the file descriptors
    close(fd1);
    close(fd2);

    // Call the function-under-test
    hts_idx_t *index = hts_idx_load2(tmpl1, tmpl2);

    // Clean up
    if (index != NULL) {
        hts_idx_destroy(index);
    }

    // Remove the temporary files
    remove(tmpl1);
    remove(tmpl2);

    return 0;
}