#include <stdint.h>
#include <stddef.h>
#include "zlib.h"
#include <stdio.h>
#include <stdlib.h>
#include "unistd.h"
#include <string.h>  // Include for memcpy()

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
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


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function compress with uncompress
    if (uncompress(compressedData, &compressedSize, data, size) != Z_OK) {
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


        free(compressedData);
        close(fd);
        unlink(filename);
        return 0;
    }

    // Write the compressed data to the temporary file

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from uncompress to compress2
    uLong ret_zlibCompileFlags_zehwh = zlibCompileFlags();
    int ret_gzrewind_volwo = gzrewind(0);
    if (ret_gzrewind_volwo < 0){
    	return 0;
    }

    int ret_compress2_rtfqe = compress2(NULL, NULL, compressedData, ret_zlibCompileFlags_zehwh, ret_gzrewind_volwo);
    if (ret_compress2_rtfqe < 0){
    	return 0;
    }

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