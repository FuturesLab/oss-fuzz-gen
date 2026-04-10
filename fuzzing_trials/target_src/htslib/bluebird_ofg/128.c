#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "htslib/hts.h"

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    htsFile *file = NULL;
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

    // Open the temporary file with hts_open
    file = hts_open(tmpl, "r");
    if (file == NULL) {
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hts_flush with hts_check_EOF

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_open to hts_idx_seqnames
    int ret_hfile_has_plugin_rehhw = hfile_has_plugin((const char *)data);
    if (ret_hfile_has_plugin_rehhw < 0){
    	return 0;
    }

    const char** ret_hts_idx_seqnames_pwmol = hts_idx_seqnames(NULL, &ret_hfile_has_plugin_rehhw, 0, (void *)file);
    if (ret_hts_idx_seqnames_pwmol == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    hts_check_EOF(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Close the file and clean up
    hts_close(file);
    unlink(tmpl);

    return 0;
}