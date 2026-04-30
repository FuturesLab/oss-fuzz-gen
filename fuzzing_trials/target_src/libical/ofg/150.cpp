#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to be used as a string
    char *source = (char *)malloc(size + 1);
    if (!source) {
        return 0;
    }
    memcpy(source, data, size);
    source[size] = '\0';

    // Create a dummy icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (!prop) {
        free(source);
        return 0;
    }

    // Call the function under test
    icalproperty_set_source(prop, source);

    // Clean up
    icalproperty_free(prop);
    free(source);

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

    LLVMFuzzerTestOneInput_150(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
