#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    z_stream stream;
    const Bytef *dictionary;
    uInt dictLength;
    int result;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = 0;
    stream.next_in = Z_NULL;

    // Initialize inflate state
    if (inflateInit(&stream) != Z_OK) {
        return 0;
    }

    // Ensure the dictionary is not NULL and has a positive length
    if (size > 0) {
        dictionary = data;
        dictLength = (uInt)size;
    } else {
        // Use a default dictionary if size is 0
        static const Bytef defaultDict[] = {0x01, 0x02, 0x03, 0x04};
        dictionary = defaultDict;
        dictLength = sizeof(defaultDict);
    }

    // Call the function-under-test
    result = inflateSetDictionary(&stream, dictionary, dictLength);

    // Check if setting the dictionary was successful
    if (result == Z_OK) {
        // Prepare some compressed data to decompress
        static const Bytef compressedData[] = {0x78, 0x9c, 0x63, 0x60, 0x60, 0x04, 0x00, 0x00, 0x18, 0x00, 0x05};
        Bytef decompressedData[100];
        stream.avail_in = sizeof(compressedData);
        stream.next_in = (Bytef *)compressedData;
        stream.avail_out = sizeof(decompressedData);
        stream.next_out = decompressedData;

        // Perform the decompression
        inflate(&stream, Z_NO_FLUSH);
    }

    // Clean up and free resources
    inflateEnd(&stream);

    return 0;
}