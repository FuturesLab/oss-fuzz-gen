#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    GF_ISOCompressMode compress_mode;
    u32 compress_flags;

    // Ensure size is sufficient for our needs
    if (size < sizeof(GF_ISOCompressMode) + sizeof(u32)) {
        return 0;
    }

    // Initialize the file (for the purpose of this example, we assume it's non-NULL)
    // In a real-world scenario, you would need to create or open an actual GF_ISOFile.
    // Here we just assume the file pointer is valid for fuzzing purposes.
    file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL); // Opening a dummy file

    // Extract compress_mode and compress_flags from the input data
    compress_mode = *((GF_ISOCompressMode *)data);
    compress_flags = *((u32 *)(data + sizeof(GF_ISOCompressMode)));

    // Call the function-under-test
    gf_isom_enable_compression(file, compress_mode, compress_flags);

    // Clean up
    if (file != NULL) {
        gf_isom_close(file);
    }

    return 0;
}