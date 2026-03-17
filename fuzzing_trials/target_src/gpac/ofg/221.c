#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Required for close() and mkstemp()
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_221(const uint8_t *data, size_t size) {
    GF_ISOFile *file = gf_isom_open("test.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (file == NULL) {
        return 0;
    }

    Bool root_meta = 1;
    u32 track_num = 1;

    // Create a temporary file for XMLFileName
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        gf_isom_close(file);
        return 0;
    }
    close(fd);

    // Write the data to the temporary file
    FILE *xmlFile = fopen(tmpl, "wb");
    if (xmlFile == NULL) {
        gf_isom_close(file);
        return 0;
    }
    fwrite(data, 1, size, xmlFile);
    fclose(xmlFile);

    unsigned char *xmlData = (unsigned char *)malloc(size);
    if (xmlData == NULL) {
        gf_isom_close(file);
        return 0;
    }
    memcpy(xmlData, data, size);

    Bool IsBinaryXML = 0;

    // Call the function-under-test
    gf_isom_set_meta_xml(file, root_meta, track_num, tmpl, xmlData, size, IsBinaryXML);

    // Clean up
    free(xmlData);
    gf_isom_close(file);
    remove(tmpl);

    return 0;
}