#include <gpac/isomedia.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>  // Include for FILE operations and fopen

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    GF_ISOFile *file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!file) return 0;

    // Ensure the data size is not zero for valid operation
    if (size == 0) {
        gf_isom_close(file);
        return 0;
    }

    // Create a temporary file for XMLFileName
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        gf_isom_close(file);
        return 0;
    }
    close(fd);

    // Write the fuzz data to the temporary file
    FILE *xmlFile = fopen(tmpl, "wb");
    if (xmlFile) {
        fwrite(data, 1, size, xmlFile);
        fclose(xmlFile);
    } else {
        gf_isom_close(file);
        return 0;
    }

    // Call the function-under-test
    gf_isom_set_meta_xml(file, 1, 1, tmpl, (unsigned char *)data, (u32)size, 0);

    // Clean up
    unlink(tmpl);
    gf_isom_close(file);

    return 0;
}