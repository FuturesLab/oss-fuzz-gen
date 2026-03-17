#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // For memcpy
#include <unistd.h>  // For close
#include <gpac/isomedia.h>
#include <gpac/constants.h>
#include <gpac/tools.h>

int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {
    GF_ISOFile *file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!file) {
        return 0;
    }

    // Ensure the size is sufficient to avoid out-of-bounds access
    if (size < 1) {
        gf_isom_close(file);
        return 0;
    }

    // Create a temporary file for the XML
    char tmpl[] = "/tmp/fuzz_xmlXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        gf_isom_close(file);
        return 0;
    }
    close(fd);

    // Write the data to the temporary file
    FILE *xmlFile = fopen(tmpl, "wb");
    if (!xmlFile) {
        gf_isom_close(file);
        return 0;
    }
    fwrite(data, 1, size, xmlFile);
    fclose(xmlFile);

    Bool root_meta = GF_TRUE;
    u32 track_num = 1;
    unsigned char *data_copy = (unsigned char *)malloc(size);
    if (!data_copy) {
        remove(tmpl);
        gf_isom_close(file);
        return 0;
    }
    memcpy(data_copy, data, size);
    u32 data_size = size;
    Bool IsBinaryXML = GF_FALSE;

    gf_isom_set_meta_xml(file, root_meta, track_num, tmpl, data_copy, data_size, IsBinaryXML);

    free(data_copy);
    remove(tmpl);
    gf_isom_close(file);

    return 0;
}