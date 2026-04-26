#include <stdint.h>
#include <stddef.h>

// Include the necessary libical headers
extern "C" {
    #include <libical/ical.h>
}

// Correct the type name to match the actual enumeration type in libical
extern "C" {
    void icalproperty_set_xlicclass(icalproperty *, icalproperty_xlicclass);
}

extern "C" int LLVMFuzzerTestOneInput_232(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract an enumeration value
    if (size < sizeof(icalproperty_xlicclass)) {
        return 0;
    }

    // Create a new icalproperty
    icalproperty *property = icalproperty_new(ICAL_XLICCLASS_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Extract an enumeration value from the input data
    icalproperty_xlicclass xlicclass_value = 
        static_cast<icalproperty_xlicclass>(data[0]);

    // Call the function-under-test
    icalproperty_set_xlicclass(property, xlicclass_value);

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

    LLVMFuzzerTestOneInput_232(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
