#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "htslib/hts.h"

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of hts_open
    const char uizqxllp[1024] = "crdjp";
    file = hts_open(tmpl, uizqxllp);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (file == NULL) {
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hts_flush with hts_check_EOF
    hts_check_EOF(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Close the file and clean up
    hts_close(file);
    unlink(tmpl);

    return 0;
}