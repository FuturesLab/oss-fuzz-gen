#include <cstdint> // Include for uint8_t
#include <cstdlib> // Include for malloc and free
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_243(const uint8_t *data, size_t size) {
    // Initialize an icalproperty object
    icalproperty *property = icalproperty_new(ICAL_FREEBUSY_PROPERTY);

    if (property == NULL) {
        return 0; // Return if property creation failed
    }

    // Create a temporary buffer to hold the input data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        icalproperty_free(property);
        return 0; // Return if memory allocation failed
    }

    // Copy the input data to the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Set the freebusy property with the input data
    icalproperty_set_freebusy(property, icalperiodtype_from_string(buffer));

    // Call the function-under-test
    struct icalperiodtype period = icalproperty_get_freebusy(property);

    // Clean up
    free(buffer);
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

    LLVMFuzzerTestOneInput_243(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
