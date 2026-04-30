#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_1228(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalparser *parser = icalparser_new();

    // Since icalparser_new() does not take any input arguments, we don't need to use `data` or `size` here.
    // However, we should clean up by freeing the parser if it was successfully created.
    if (parser != NULL) {
        icalparser_free(parser);
    }

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

    LLVMFuzzerTestOneInput_1228(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
