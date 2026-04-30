#include <stdint.h>
#include <stddef.h>

// Include the libical header within extern "C" to handle C linkage
extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_300(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to extract an enumeration value
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer value from the input data to use as the enumeration value
    int enum_value = *(reinterpret_cast<const int*>(data));

    // Cast the extracted integer to the enumeration type
    icalproperty_method method = static_cast<icalproperty_method>(enum_value);

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_method(method, NULL);

    // Clean up if necessary
    if (property != NULL) {
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

    LLVMFuzzerTestOneInput_300(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
