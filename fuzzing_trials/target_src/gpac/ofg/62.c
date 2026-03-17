#include <gpac/isomedia.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h> // Include for close() and mkstemp()

int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for the necessary parameters
    if (size < sizeof(u32) + 1) {
        return 0;
    }

    // Initialize GF_ISOFile
    GF_ISOFile *file = gf_isom_open(NULL, GF_ISOM_OPEN_READ, NULL);
    if (!file) {
        return 0;
    }

    // Extract parameters from the data
    Bool root_meta = (Bool)data[0];
    u32 track_num = *(u32 *)(data + 1);

    // Create a temporary file for outName
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        gf_isom_close(file);
        return 0;
    }
    close(fd);

    // Initialize is_binary
    Bool is_binary = GF_FALSE;

    // Call the function-under-test
    gf_isom_extract_meta_xml(file, root_meta, track_num, tmpl, &is_binary);

    // Clean up
    remove(tmpl);
    gf_isom_close(file);

    return 0;
}