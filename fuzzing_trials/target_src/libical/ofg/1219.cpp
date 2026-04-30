#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1219(const uint8_t *data, size_t size) {
    // Ensure there is enough data to process
    if (size < 1) {
        return 0;
    }

    // Initialize an icalproperty object with a random property kind
    icalproperty_kind kind = static_cast<icalproperty_kind>(data[0] % ICAL_NO_PROPERTY);
    icalproperty *property = icalproperty_new(kind);

    // Ensure that the property is not NULL
    if (property == NULL) {
        return 0;
    }

    // Create a buffer to store the remaining data as a string
    char *buffer = (char *)malloc(size);
    if (buffer == NULL) {
        icalproperty_free(property);
        return 0;
    }

    // Copy the remaining data into the buffer and null-terminate it
    memcpy(buffer, data + 1, size - 1);
    buffer[size - 1] = '\0';

    // Set the property value using the fuzz data
    icalvalue *value = icalvalue_new_string(buffer);
    if (value != NULL) {
        icalproperty_set_value(property, value);
    }

    // Call the function-under-test
    struct icaltimetype maxdate = icalproperty_get_maxdate(property);

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

    LLVMFuzzerTestOneInput_1219(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
