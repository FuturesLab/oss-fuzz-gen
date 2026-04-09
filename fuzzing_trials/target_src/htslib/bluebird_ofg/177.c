#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/hts.h"
#include "/src/htslib/htslib/kstring.h"
#include "htslib/hfile.h"
#include "htslib/vcf.h" // Correct inclusion for bcf_hdr_t and related functions

int LLVMFuzzerTestOneInput_177(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid input for bcf_hdr_init
    if (size == 0) {
        return 0;
    }

    // Create a memory stream from the input data
    htsFile *mem_file = hts_open_format("mem:", "r", NULL);
    if (!mem_file) {
        return 0;
    }

    // Write the input data to the memory stream
    if (hwrite(mem_file->fp.hfile, data, size) != size) {
        hts_close(mem_file);
        return 0;
    }

    // Rewind the memory stream to the beginning
    if (hseek(mem_file->fp.hfile, 0, SEEK_SET) != 0) {
        hts_close(mem_file);
        return 0;
    }

    // Read a VCF header from the memory stream
    bcf_hdr_t *hdr = bcf_hdr_read(mem_file);
    if (!hdr) {
        hts_close(mem_file);
        return 0;
    }

    // Call the function-under-test
    bcf_hdr_destroy(hdr);

    // Close the memory stream
    hts_close(mem_file);

    return 0;
}