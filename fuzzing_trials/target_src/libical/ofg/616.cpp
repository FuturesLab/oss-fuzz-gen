#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
    #include <libical/icalparameter.h>
}

// Ensure that ICALPARAMETER_FIRST and ICALPARAMETER_LAST are included
extern "C" {
    #include <libical/icalparameter.h>
}

extern "C" int LLVMFuzzerTestOneInput_616(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create the necessary structures
    if (size < 2) {
        return 0;
    }

    // Initialize libical library
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Create a parameter
    icalparameter_kind kind = static_cast<icalparameter_kind>(data[0] % (ICALPARAMETER_LAST_ENUM + 1)); // Use ICALPARAMETER_LAST_ENUM for the last valid kind
    icalparameter *parameter = icalparameter_new(kind);
    if (parameter == NULL) {
        icalproperty_free(property);
        return 0;
    }

    // Call the function-under-test
    icalproperty_add_parameter(property, parameter);

    // Clean up
    icalproperty_free(property);
    // Note: The parameter is freed when the property is freed

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

    LLVMFuzzerTestOneInput_616(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
