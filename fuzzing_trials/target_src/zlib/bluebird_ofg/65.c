#include <stdint.h>
#include <stddef.h>
#include "zlib.h"
#include <stdio.h>
#include <stdlib.h>
#include "unistd.h"
#include <string.h>  // Include for memcpy()

int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char filename[] = "/tmp/fuzz_gzoffset_XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    // Compress the input data
    uLongf compressedSize = compressBound(size);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from compressBound to crc32_combine
    off_t ret_gztell_bdzcl = gztell(0);

    uLong ret_crc32_combine_bfdmj = crc32_combine(compressedSize, 0, ret_gztell_bdzcl);

    // End mutation: Producer.APPEND_MUTATOR

    uint8_t *compressedData = (uint8_t *)malloc(compressedSize);
    if (compressedData == NULL) {
        close(fd);
        unlink(filename);
        return 0;
    }


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function compress with uncompress
    if (uncompress(compressedData, &compressedSize, data, size) != Z_OK) {
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


        free(compressedData);
        close(fd);
        unlink(filename);
        return 0;
    }

    // Write the compressed data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == NULL) {
        free(compressedData);
        close(fd);
        return 0;
    }
    fwrite(compressedData, 1, compressedSize, file);
    fclose(file);
    free(compressedData);

    // Open the file as a gzFile
    gzFile gzfile = gzopen(filename, "rb");
    if (gzfile == NULL) {
        unlink(filename);
        return 0;
    }

    // Call the function-under-test
    off_t offset = gzoffset(gzfile);

    // Clean up
    gzclose(gzfile);
    unlink(filename);

    return 0;
}