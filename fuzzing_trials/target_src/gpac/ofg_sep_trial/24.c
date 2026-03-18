#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for extracting parameters
    if (size < sizeof(uint32_t) + sizeof(int32_t)) {
        return 0;
    }

    // Initialize variables
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Extract trackNumber and timeOffset from the input data
    uint32_t trackNumber = *((uint32_t *)data);
    int32_t timeOffset = *((int32_t *)(data + sizeof(uint32_t)));

    // Call the function-under-test
    gf_isom_rtp_packet_set_offset(the_file, trackNumber, timeOffset);

    // Close the file
    gf_isom_close(the_file);

    return 0;
}