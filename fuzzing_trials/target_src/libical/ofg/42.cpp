#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to create a parser and some data
    if (size < 1) return 0;

    // Initialize the icalparser object
    icalparser *parser = icalparser_new();
    if (parser == NULL) return 0;

    // Use the data to create a non-NULL pointer for the second parameter
    void *gen_data = (void *)data;

    // Call the function-under-test
    icalparser_set_gen_data(parser, gen_data);

    // Clean up
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

    LLVMFuzzerTestOneInput_42(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
