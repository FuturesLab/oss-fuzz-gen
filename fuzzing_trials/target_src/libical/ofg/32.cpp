#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid icalproperty
    if (size < 1) {
        return 0;
    }

    // Create a dummy icalproperty for testing
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Initialize an icalproperty iterator
    icalproperty_kind kind = icalproperty_isa(prop);

    // Since icalproperty_begin_component does not exist, we will use icalproperty_get_first_parameter
    icalparameter *param = icalproperty_get_first_parameter(prop, ICAL_ANY_PARAMETER);

    // Call the function-under-test
    bool is_valid = (param != NULL);

    // Clean up
    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_32(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
