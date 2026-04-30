#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    // Initialize the library
    icalerror_set_error_state(ICAL_MALFORMEDDATA_ERROR, ICAL_ERROR_NONFATAL);

    // Ensure data is large enough to contain a valid enum value
    if (size < sizeof(enum icalproperty_xlicclass)) {
        return 0;
    }

    // Cast the input data to an enum icalproperty_xlicclass
    enum icalproperty_xlicclass xlicclass = static_cast<enum icalproperty_xlicclass>(*data);

    // Create a new icalproperty
    icalproperty *property = icalproperty_new_xlicclass(xlicclass);

    if (property != NULL) {
        // Call the function-under-test
        icalproperty_xlicclass result = icalproperty_get_xlicclass(property);

        // Clean up
        icalproperty_free(property);
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

    LLVMFuzzerTestOneInput_19(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
