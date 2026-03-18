#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Ensure there is enough data for the trackNumber and nameUTF8
    if (size < sizeof(uint32_t) + 1) {
        return 0;
    }

    // Initialize GF_ISOFile
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Extract trackNumber from the data
    uint32_t trackNumber;
    memcpy(&trackNumber, data, sizeof(uint32_t));

    // Use the rest of the data as the nameUTF8
    const char *nameUTF8 = (const char *)(data + sizeof(uint32_t));
    size_t nameLength = size - sizeof(uint32_t);

    // Ensure nameUTF8 is null-terminated
    char *nameBuffer = (char *)malloc(nameLength + 1);
    if (!nameBuffer) {
        gf_isom_close(the_file);
        return 0;
    }
    memcpy(nameBuffer, nameUTF8, nameLength);
    nameBuffer[nameLength] = '\0';

    // Call the function-under-test
    gf_isom_set_handler_name(the_file, trackNumber, nameBuffer);

    // Clean up
    free(nameBuffer);
    gf_isom_close(the_file);

    return 0;
}