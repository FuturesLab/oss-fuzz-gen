#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_594(const uint8_t *data, size_t size) {
    // Initialize the fuzzing input
    if (size < 2) { // Ensure there's enough data for meaningful operations
        return 0;
    }

    // Create a new icalproperty with a specific type based on input
    icalproperty_kind prop_kind = static_cast<icalproperty_kind>(data[0] % ICAL_NO_PROPERTY);
    icalproperty *prop = icalproperty_new(prop_kind);
    if (prop == NULL) {
        return 0;
    }

    // Use the second byte of data to determine the parameter kind
    icalparameter_kind param_kind = static_cast<icalparameter_kind>(data[1] % ICAL_NO_PARAMETER);

    // Create a new icalparameter and add it to the property
    icalparameter *param = icalparameter_new(param_kind);
    if (param != NULL) {
        icalproperty_add_parameter(prop, param);
    }

    // Call the function-under-test
    icalproperty_remove_parameter_by_kind(prop, param_kind);

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

    LLVMFuzzerTestOneInput_594(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
