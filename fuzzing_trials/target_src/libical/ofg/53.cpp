#include <cstdint>
#include <cstdlib>
#include <libical/ical.h>

extern "C" {
    // Include the necessary libical headers
    #include <libical/ical.h>
    #include <libical/icalproperty.h>

    // Ensure that the function signature is included
    void icalproperty_set_querylevel(icalproperty *, icalproperty_querylevel);
}

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    if (size < 2) { // Ensure there's enough data to use for fuzzing
        return 0;
    }

    // Initialize an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_QUERYLEVEL_PROPERTY);
    if (prop == NULL) {
        return 0; // If initialization fails, exit
    }

    // Use the first byte of data to determine the query level
    icalproperty_querylevel query_level = static_cast<icalproperty_querylevel>(data[0] % 3);

    // Use the second byte of data to set a value for the property
    char value[2] = {static_cast<char>(data[1]), '\0'};
    icalproperty_set_value(prop, icalvalue_new_string(value));

    // Call the function-under-test
    icalproperty_set_querylevel(prop, query_level);

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

    LLVMFuzzerTestOneInput_53(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
