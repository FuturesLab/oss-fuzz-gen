#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/aom/aom/aom_codec.h"
    #include "aom/aom_decoder.h"
    #include "aom/aomdx.h" // Include the header where aom_codec_av1_dx is declared
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Initialize the codec interface for AV1 decoding
    aom_codec_iface_t *iface = aom_codec_av1_dx();

    // Create a codec context
    aom_codec_ctx_t codec;
    if (aom_codec_dec_init(&codec, iface, NULL, 0) != AOM_CODEC_OK) {
        return 0; // If initialization fails, exit early
    }

    // Decode the input data
    if (aom_codec_decode(&codec, data, size, NULL) != AOM_CODEC_OK) {
        aom_codec_destroy(&codec);
        return 0; // If decoding fails, clean up and exit
    }

    // Clean up and destroy the codec context
    aom_codec_destroy(&codec);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_8(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
