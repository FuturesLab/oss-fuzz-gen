#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_1060(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for fuzzing
    if (size < 1) {
        return 0;
    }

    // Create a dummy icalproperty
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Use the first byte of data to determine the icalparameter_kind
    icalparameter_kind kind = static_cast<icalparameter_kind>(data[0] % ICAL_NO_PARAMETER);

    // Call the function-under-test
    icalparamiter iter = icalproperty_begin_parameter(prop, kind);

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

    LLVMFuzzerTestOneInput_1060(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
