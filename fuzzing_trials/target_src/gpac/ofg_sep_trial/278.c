#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_278(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    FILE *temp_file = fopen("temp.mp4", "wb");
    if (!temp_file) {
        return 0;
    }
    fwrite(data, 1, size, temp_file);
    fclose(temp_file);

    GF_ISOFile *the_file = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    u32 trackNumber = 1; // Example track number
    GF_AVCConfig cfg;
    memset(&cfg, 0, sizeof(GF_AVCConfig)); // Initialize the AVCConfig structure

    // Ensure URLname and URNname are null-terminated strings
    const char *URLname = "http://example.com";
    const char *URNname = "urn:example";

    u32 outDescriptionIndex = 0;

    // Call the function-under-test
    gf_isom_mvc_config_new(the_file, trackNumber, &cfg, URLname, URNname, &outDescriptionIndex);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}