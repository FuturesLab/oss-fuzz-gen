#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>  // Include this for close() and unlink()
#include <fcntl.h>   // Include this for mkstemp()
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_245(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = NULL;
    u32 trackNumber = 1;
    u32 sampleDescriptionIndex = 1;
    u32 container_type = 0;
    Bool default_IsEncrypted = 0;
    u32 crypt_byte_block = 0;
    u32 skip_byte_block = 0;
    const u8 *key_info = NULL;
    u32 key_info_size = 0;

    // Create a temporary file to simulate an ISO file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    write(fd, data, size);
    close(fd);

    // Open the ISO file
    the_file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (!the_file) {
        // Clean up the temporary file
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    gf_isom_cenc_get_default_info(the_file, trackNumber, sampleDescriptionIndex,
                                  &container_type, &default_IsEncrypted,
                                  &crypt_byte_block, &skip_byte_block,
                                  &key_info, &key_info_size);

    // Close the ISO file and clean up
    gf_isom_close(the_file);
    unlink(tmpl);

    return 0;
}