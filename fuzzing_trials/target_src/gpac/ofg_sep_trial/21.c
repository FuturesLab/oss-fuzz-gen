#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for trackNumber and at least a small string
    if (size < sizeof(u32) + 1) {
        return 0;
    }

    // Initialize GF_ISOFile
    GF_ISOFile *the_file = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Extract trackNumber from the input data
    u32 trackNumber = *((u32 *)data);
    data += sizeof(u32);
    size -= sizeof(u32);

    // Use the remaining data as the nameUTF8
    char *nameUTF8 = (char *)malloc(size + 1);
    if (!nameUTF8) {
        gf_isom_close(the_file);
        return 0;
    }
    memcpy(nameUTF8, data, size);
    nameUTF8[size] = '\0'; // Ensure null-terminated string

    // Call the function-under-test
    gf_isom_set_handler_name(the_file, trackNumber, nameUTF8);

    // Clean up
    free(nameUTF8);
    gf_isom_close(the_file);

    return 0;
}