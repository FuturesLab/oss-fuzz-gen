#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <htslib/hts.h>
#include <htslib/bgzf.h>
#include <htslib/sam.h>
#include <htslib/hts_defs.h>
#include <htslib/hts_log.h>

int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    if (fwrite(data, 1, size, temp_file) != size) {
        fclose(temp_file);
        return 0;
    }

    // Rewind the file to the beginning for reading
    rewind(temp_file);

    // Open the temporary file with BGZF
    BGZF *bgzf = bgzf_dopen(fileno(temp_file), "r");
    if (bgzf == NULL) {
        fclose(temp_file);
        return 0;
    }

    // Initialize iterator
    hts_itr_t *iter = hts_itr_query(bgzf, NULL, 0, 0, 0);
    if (iter == NULL) {
        bgzf_close(bgzf);
        fclose(temp_file);
        return 0;
    }

    // Allocate memory for a dummy bam1_t structure
    bam1_t *b = bam_init1();
    if (b == NULL) {
        hts_itr_destroy(iter);
        bgzf_close(bgzf);
        fclose(temp_file);
        return 0;
    }

    // Call the function-under-test
    int result = hts_itr_next(bgzf, iter, b, NULL);

    // Clean up
    bam_destroy1(b);
    hts_itr_destroy(iter);
    bgzf_close(bgzf);
    fclose(temp_file);

    return 0;
}