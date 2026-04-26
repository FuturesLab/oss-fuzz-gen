#include <cstddef>
#include <cstdint>
#include <cstdarg>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
    #include <libical/icalparameter.h> // Include the header for icalparameter functions
}

extern "C" int LLVMFuzzerTestOneInput_515(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract a valid string
    if (size < 1) return 0;

    // Allocate a buffer for the string and ensure it's null-terminated
    char *name = new char[size + 1];
    memcpy(name, data, size);
    name[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_name(name, nullptr);

    // Check if the property was created successfully
    if (prop != nullptr) {
        // Perform additional operations to increase code coverage
        icalproperty_kind kind = icalproperty_isa(prop);
        if (kind == ICAL_X_PROPERTY) {
            // If it's an X property, attempt to set a parameter
            icalparameter *xparam = icalparameter_new(ICAL_X_PARAMETER);
            if (xparam != nullptr) {
                icalparameter_set_xname(xparam, "X-PARAM");
                icalparameter_set_xvalue(xparam, "VALUE");
                icalproperty_set_parameter(prop, xparam);
                icalparameter_free(xparam); // Free the parameter after use
            }
        }

        // Attempt to retrieve the name to ensure the property is being used
        const char *retrieved_name = icalproperty_get_name(prop);
        if (retrieved_name != nullptr) {
            // Perform some operation with the retrieved name to ensure it's used
            if (strcmp(retrieved_name, name) == 0) {
                // This is just a placeholder to show that the name was retrieved
                // and matches the input name
            }
        }

        // Free the property
        icalproperty_free(prop);
    }

    // Clean up
    delete[] name;

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

    LLVMFuzzerTestOneInput_515(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
