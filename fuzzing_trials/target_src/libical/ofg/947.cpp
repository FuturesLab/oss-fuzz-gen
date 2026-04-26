#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_947(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the icalproperty
    struct icaltimetype null_time = icaltime_null_time();
    struct icalperiodtype null_period = icalperiodtype_null_period();
    struct icaldatetimeperiodtype dtp;
    dtp.time = null_time;
    dtp.period = null_period;
    icalproperty *prop = icalproperty_new_rdate(dtp);

    // Create a temporary buffer to hold the input data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == nullptr) {
        icalproperty_free(prop);
        return 0;
    }

    // Copy the input data into the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Convert the buffer to an icaltimetype
    struct icaltimetype time = icaltime_from_string(buffer);

    // Create a period using the time and a null period
    struct icaldatetimeperiodtype period;
    period.time = time;
    period.period = null_period;

    // Set the property value using the input data
    icalproperty_set_rdate(prop, period);

    // Call the function-under-test
    struct icaldatetimeperiodtype result = icalproperty_get_rdate(prop);

    // Clean up
    free(buffer);
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

    LLVMFuzzerTestOneInput_947(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
