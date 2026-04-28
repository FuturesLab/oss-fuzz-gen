#include <cstdint>
#include <cstdlib>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_890(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a valid icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Create an icaltimetype from the input data
    struct icaltimetype dtstart;
    dtstart.year = (int16_t)data[0] + ((int16_t)data[1] << 8);
    dtstart.month = data[2] % 12 + 1;  // Ensure month is between 1 and 12
    dtstart.day = data[3] % 31 + 1;    // Ensure day is between 1 and 31
    dtstart.hour = data[4] % 24;       // Ensure hour is between 0 and 23
    dtstart.minute = data[5] % 60;     // Ensure minute is between 0 and 59
    dtstart.second = data[6] % 60;     // Ensure second is between 0 and 59
    dtstart.is_date = data[7] % 2;     // Ensure is_date is 0 or 1

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_dtstart(dtstart);

    // Clean up
    if (prop != NULL) {
        icalproperty_free(prop);
    }

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

    LLVMFuzzerTestOneInput_890(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
