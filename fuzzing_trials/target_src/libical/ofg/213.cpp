#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_213(const uint8_t *data, size_t size) {
    // Ensure there is enough data to use
    if (size < 2) {
        return 0;
    }

    // Initialize the icalproperty object
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Use the first byte of data to determine the icalparameter_kind
    icalparameter_kind kind = static_cast<icalparameter_kind>(data[0] % ICAL_NO_PARAMETER);

    // Call the function-under-test
    icalparameter *parameter = icalproperty_get_first_parameter(property, kind);

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

    LLVMFuzzerTestOneInput_213(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
