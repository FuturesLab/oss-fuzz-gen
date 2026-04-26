#include <stdint.h>
#include <stddef.h>

// Include the necessary libical headers
extern "C" {
    #include <libical/ical.h>
    #include <libical/icalproperty.h>
    #include <libical/icalenums.h> // Include the header where ICALPROPERTY_POLL_COMPLETION_MAX is defined
    #include <libical/icalderivedproperty.h> // Include the header where ICALPROPERTY_POLL_COMPLETION_MAX might be defined
}

extern "C" int LLVMFuzzerTestOneInput_974(const uint8_t *data, size_t size) {
    // Initialize the icalproperty object
    icalproperty *property = icalproperty_new(ICAL_NO_PROPERTY);
    if (property == NULL) {
        return 0; // Exit if property creation fails
    }

    // Ensure that size is sufficient to extract a value for enumeration
    if (size < sizeof(enum icalproperty_pollcompletion)) {
        icalproperty_free(property);
        return 0;
    }

    // Extract a value for the enumeration from the data
    enum icalproperty_pollcompletion pollcompletion_value =
        static_cast<enum icalproperty_pollcompletion>(data[0] % ICAL_POLLCOMPLETION_X);

    // Call the function-under-test
    icalproperty_set_pollcompletion(property, pollcompletion_value);

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

    LLVMFuzzerTestOneInput_974(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
