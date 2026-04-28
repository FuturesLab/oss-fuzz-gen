#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>

    // Function signature from the given task
    void icalproperty_set_xlicclass(icalproperty *, icalproperty_xlicclass);
}

extern "C" int LLVMFuzzerTestOneInput_233(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a valid enumeration
    if (size < sizeof(icalproperty_xlicclass)) {
        return 0;
    }

    // Initialize the icalproperty object
    icalproperty *property = icalproperty_new(ICAL_XLICCLASS_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Extract an enumeration value from the input data
    icalproperty_xlicclass xlicclassValue =
        static_cast<icalproperty_xlicclass>(data[0]);

    // Call the function-under-test
    icalproperty_set_xlicclass(property, xlicclassValue);

    // Clean up
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_233(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
