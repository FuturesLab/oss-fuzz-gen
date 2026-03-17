#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <stdio.h> // Include for file operations

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to extract necessary values
    if (size < sizeof(GF_ISOCompressMode) + sizeof(u32)) {
        return 0;
    }

    // Create a temporary file to simulate file input
    FILE *temp_file = tmpfile();
    if (!temp_file) {
        return 0;
    }

    // Write the data to the temporary file
    fwrite(data, 1, size, temp_file);
    rewind(temp_file);

    // Create a temporary directory path for the third argument
    const char *temp_dir = "/tmp"; // Assuming a Unix-like system

    // Initialize the GF_ISOFile using the temporary file
    GF_ISOFile *file = gf_isom_open(temp_file, GF_ISOM_OPEN_WRITE, temp_dir);
    if (!file) {
        fclose(temp_file);
        return 0;
    }

    // Extract GF_ISOCompressMode from data
    GF_ISOCompressMode compress_mode = *(GF_ISOCompressMode*)data;
    data += sizeof(GF_ISOCompressMode);
    size -= sizeof(GF_ISOCompressMode);

    // Extract u32 compress_flags from data
    u32 compress_flags = *(u32*)data;

    // Call the function-under-test
    gf_isom_enable_compression(file, compress_mode, compress_flags);

    // Close the file
    gf_isom_close(file);
    fclose(temp_file);

    return 0;
}