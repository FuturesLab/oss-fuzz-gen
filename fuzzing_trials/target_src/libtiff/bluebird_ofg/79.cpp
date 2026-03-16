extern "C" {
    #include "tiffio.h"
    #include <stdint.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h> // Include for close function
}

extern "C" int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to extract necessary parameters
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Create a temporary TIFF file in memory
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb+");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fseek(file, 0, SEEK_SET);

    // Open the TIFF file
    TIFF *tiff = TIFFFdOpen(fd, tmpl, "r+");
    if (tiff == NULL) {
        fclose(file);
        return 0;
    }

    // Extract the tag from the input data
    uint32_t tag;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from TIFFFdOpen to TIFFDefaultTileSize
    double ret_LogL10toY_dsexb = LogL10toY(V_NEU);
    if (ret_LogL10toY_dsexb < 0){
    	return 0;
    }
    uint32_t twdyvzht = size;

    TIFFDefaultTileSize(tiff, (uint32_t *)&ret_LogL10toY_dsexb, &twdyvzht);

    // End mutation: Producer.APPEND_MUTATOR

    memcpy(&tag, data, sizeof(uint32_t));

    // Prepare a dummy value (non-NULL) to pass to TIFFSetField
    void *value = (void *)(data + sizeof(uint32_t));

    // Call the function-under-test
    TIFFSetField(tiff, tag, value);

    // Clean up

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function TIFFClose with TIFFCleanup
    TIFFCleanup(tiff);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    fclose(file);
    remove(tmpl);

    return 0;
}