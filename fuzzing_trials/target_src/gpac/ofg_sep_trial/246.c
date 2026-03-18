#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h> // Assuming this is the correct header for the function

extern int LLVMFuzzerTestOneInput_246(const uint8_t *data, size_t size) {
    // Initialize variables
    // Since gf_isom_open expects a file name, we need to write the data to a temporary file
    const char *temp_file = "/tmp/fuzz_temp_file.mp4";
    FILE *file = fopen(temp_file, "wb");
    if (!file) {
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file using the gf_isom_open function
    GF_ISOFile *the_file = gf_isom_open(temp_file, GF_ISOM_OPEN_READ, NULL); // Use library function to open the file

    // Ensure the_file is not NULL
    if (the_file == NULL) {
        // Clean up the temporary file
        remove(temp_file);
        return 0;
    }

    u32 trackNumber = 1; // Arbitrary non-zero value
    u32 sampleDescriptionIndex = 1; // Arbitrary non-zero value
    u32 container_type = 0;
    Bool default_IsEncrypted = 0;
    u32 crypt_byte_block = 0;
    u32 skip_byte_block = 0;
    const u8 *key_info = NULL;
    u32 key_info_size = 0;

    // Call the function-under-test
    gf_isom_cenc_get_default_info(the_file, trackNumber, sampleDescriptionIndex, &container_type, &default_IsEncrypted, &crypt_byte_block, &skip_byte_block, &key_info, &key_info_size);

    // Clean up
    gf_isom_close(the_file); // Use library function to close the file
    remove(temp_file); // Remove the temporary file

    return 0;
}