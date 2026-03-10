#include <stdint.h>
#include <stddef.h>
#include "zlib.h"
#include <stdio.h>
#include <stdlib.h>
#include "unistd.h"
#include <string.h>  // Include for memcpy()

int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char filename[] = "/tmp/fuzz_gzoffset_XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    // Compress the input data
    uLongf compressedSize = compressBound(size);
    uint8_t *compressedData = (uint8_t *)malloc(compressedSize);
    if (compressedData == NULL) {
        close(fd);
        unlink(filename);
        return 0;
    }

    if (compress(compressedData, &compressedSize, data, size) != Z_OK) {
        free(compressedData);
        close(fd);
        unlink(filename);
        return 0;
    }

    // Write the compressed data to the temporary file

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from compress to adler32_z
    uLong ret_zlibCompileFlags_sgvoo = zlibCompileFlags();


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from zlibCompileFlags to uncompress

    int ret_uncompress_qezoq = uncompress(NULL, &compressedSize, NULL, ret_zlibCompileFlags_sgvoo);
    if (ret_uncompress_qezoq < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    uLong ret_adler32_z_ftwga = adler32_z(ret_zlibCompileFlags_sgvoo, compressedData, 0);

    // End mutation: Producer.APPEND_MUTATOR

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