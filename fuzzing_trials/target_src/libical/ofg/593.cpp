#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_593(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for fuzzing
    if (size < 1) {
        return 0;
    }

    // Initialize an icalproperty
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Use the first byte of data to determine the icalparameter_kind
    icalparameter_kind kind = static_cast<icalparameter_kind>(data[0] % ICAL_NO_PARAMETER);

    // Call the function-under-test
    icalproperty_remove_parameter_by_kind(property, kind);

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

    LLVMFuzzerTestOneInput_593(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
