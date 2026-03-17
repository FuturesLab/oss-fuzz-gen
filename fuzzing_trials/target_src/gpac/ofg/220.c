#include <gpac/isomedia.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

// Removed 'extern "C"' to fix the error in C code
int LLVMFuzzerTestOneInput_220(const uint8_t *data, size_t size) {
    GF_ISOFile *file = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (file == NULL) {
        return 0;
    }

    // Ensure the size is sufficient for meaningful data
    if (size < 1) {
        gf_isom_close(file);
        return 0;
    }

    // Create a temporary file for XMLFileName
    char tmpl[] = "/tmp/fuzzxmlXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        gf_isom_close(file);
        return 0;
    }
    close(fd);

    // Write some data to the temporary XML file
    FILE *xmlFile = fopen(tmpl, "w");
    if (xmlFile) {
        fwrite(data, 1, size, xmlFile);
        fclose(xmlFile);
    }

    // Set up parameters for the function call
    Bool root_meta = GF_TRUE;
    u32 track_num = 1;
    unsigned char *xml_data = (unsigned char *)malloc(size);
    if (xml_data == NULL) {
        unlink(tmpl);
        gf_isom_close(file);
        return 0;
    }
    memcpy(xml_data, data, size);
    u32 data_size = (u32)size;
    Bool IsBinaryXML = GF_FALSE;

    // Call the function-under-test
    gf_isom_set_meta_xml(file, root_meta, track_num, tmpl, xml_data, data_size, IsBinaryXML);

    // Clean up
    free(xml_data);
    unlink(tmpl);
    gf_isom_close(file);

    return 0;
}