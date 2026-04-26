#include <cstddef>
#include <cstdint>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    // Ensure there's enough data for at least one parameter
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize an icalproperty object
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    if (property == nullptr) {
        return 0;
    }

    // Instead of using va_list, directly pass the parameter
    int dummy_param = static_cast<int>(data[0]);

    // Call a function that doesn't require va_list
    // Assuming icalproperty_add_parameter is the intended function
    icalparameter *param = icalparameter_new(ICAL_ANY_PARAMETER);
    icalproperty_add_parameter(property, param);

    // Clean up
    icalproperty_free(property);
    icalparameter_free(param);

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

    LLVMFuzzerTestOneInput_123(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
