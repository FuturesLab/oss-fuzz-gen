#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_482(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_DTSTART_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *tempBuffer = (char *)malloc(size + 1);
    if (tempBuffer == NULL) {
        icalproperty_free(prop);
        return 0;
    }

    // Copy the input data to the temporary buffer and null-terminate it
    memcpy(tempBuffer, data, size);
    tempBuffer[size] = '\0';

    // Set the icalproperty value using the input data
    icalvalue *value = icalvalue_new_from_string(ICAL_DATETIME_VALUE, tempBuffer);
    if (value != NULL) {
        icalproperty_set_value(prop, value);
    }

    // Call the function-under-test
    struct icaltimetype dtstart = icalproperty_get_dtstart(prop);

    // Clean up
    icalproperty_free(prop);
    free(tempBuffer);

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

    LLVMFuzzerTestOneInput_482(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
