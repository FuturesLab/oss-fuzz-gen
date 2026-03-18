#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/internal/isomedia_dev.h> // Include this for gf_isom_open

int LLVMFuzzerTestOneInput_263(const uint8_t *data, size_t size) {
    // Create a temporary file to write the data
    char filename[] = "/tmp/fuzz_input.XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0; // If file creation fails, exit early
    }
    write(fd, data, size);
    close(fd);

    // Open the movie file from the temporary file
    GF_ISOFile *movie = gf_isom_open(filename, GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        unlink(filename);
        return 0; // If movie creation fails, exit early
    }

    GF_Descriptor *theDesc = gf_odf_desc_new(GF_ODF_OD_TAG);
    if (theDesc == NULL) {
        gf_isom_close(movie);
        unlink(filename);
        return 0; // If descriptor creation fails, exit early
    }

    // Call the function-under-test
    gf_isom_add_desc_to_root_od(movie, theDesc);

    // Clean up
    gf_odf_desc_del(theDesc);
    gf_isom_close(movie);
    unlink(filename);

    return 0;
}