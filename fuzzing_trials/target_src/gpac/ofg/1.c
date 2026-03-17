#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    u32 trackNumber = 1;
    GF_AC4Config cfg;
    cfg.stream = (GF_AC4StreamInfo){0}; // Initialize stream info
    cfg.sample_rate = 48000; // Example sample rate
    cfg.frame_size = 1024; // Example frame size
    cfg.channel_count = 2; // Example channel count
    cfg.sample_duration = 1024; // Example sample duration
    cfg.media_time_scale = 48000; // Example media time scale
    cfg.header_size = 0; // Example header size
    cfg.crc_size = 0; // Example CRC size
    cfg.toc_size = 0; // Example TOC size
    const char *URLname = "http://example.com";
    const char *URNname = "urn:example";
    u32 outDescriptionIndex = 0;

    // Ensure the_file is not NULL
    if (!the_file) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_ac4_config_new(the_file, trackNumber, &cfg, URLname, URNname, &outDescriptionIndex);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}