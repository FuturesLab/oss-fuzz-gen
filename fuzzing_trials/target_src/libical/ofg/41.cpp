#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    // Create an icalparser instance
    icalparser *parser = icalparser_new();
    if (parser == NULL) {
        return 0; // If parser creation fails, exit early
    }

    // Ensure data is not empty and size is non-zero
    if (size == 0) {
        icalparser_free(parser);
        return 0;
    }

    // Allocate a buffer for general data
    void *gen_data = malloc(size);
    if (gen_data == NULL) {
        icalparser_free(parser);
        return 0; // If memory allocation fails, exit early
    }

    // Copy data into gen_data buffer
    memcpy(gen_data, data, size);

    // Call the function-under-test
    icalparser_set_gen_data(parser, gen_data);

    // Clean up
    free(gen_data);
    icalparser_free(parser);

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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_41(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
