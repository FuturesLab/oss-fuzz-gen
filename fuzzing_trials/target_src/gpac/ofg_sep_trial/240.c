#include <stdint.h>
#include <stdlib.h>
#include <unistd.h> // for close()
#include <stdio.h>  // for remove()
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_240(const uint8_t *data, size_t size) {
    GF_ISOFile *isom_file = NULL;
    u32 trackNumber = 1; // Initialize with a non-zero value
    u32 sampleDescriptionIndex = 1; // Initialize with a non-zero value
    GF_OpusConfig opcfg;

    // Create a temporary ISO file from the input data
    if (size > 0) {
        char tmpl[] = "/tmp/fuzzfileXXXXXX";
        int fd = mkstemp(tmpl);
        if (fd != -1) {
            write(fd, data, size);
            close(fd);

            // Open the ISO file
            isom_file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
            if (isom_file != NULL) {
                // Call the function-under-test
                gf_isom_opus_config_get_desc(isom_file, trackNumber, sampleDescriptionIndex, &opcfg);

                // Close the ISO file
                gf_isom_close(isom_file);
            }

            // Remove the temporary file
            remove(tmpl);
        }
    }

    return 0;
}