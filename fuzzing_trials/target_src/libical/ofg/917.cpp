#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h> // Correctly include the necessary headers from the libical project

    // Function signature from the project-under-test
    void icalproperty_set_mindate(icalproperty *, struct icaltimetype);
}

extern "C" int LLVMFuzzerTestOneInput_917(const uint8_t *data, size_t size) {
    // Ensure we have enough data to initialize icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Create an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Initialize icaltimetype from the input data
    struct icaltimetype mindate;
    mindate.year = (int16_t)data[0] | ((int16_t)data[1] << 8);
    mindate.month = data[2] % 12 + 1; // Ensure valid month
    mindate.day = data[3] % 31 + 1;   // Ensure valid day
    mindate.hour = data[4] % 24;      // Ensure valid hour
    mindate.minute = data[5] % 60;    // Ensure valid minute
    mindate.second = data[6] % 60;    // Ensure valid second
    mindate.is_date = data[7] % 2;    // Boolean value
    mindate.is_daylight = data[8] % 2; // Boolean value for is_daylight

    // Call the function-under-test
    icalproperty_set_mindate(prop, mindate);

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

    LLVMFuzzerTestOneInput_917(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
