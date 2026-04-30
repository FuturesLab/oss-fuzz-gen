#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to fill the icaltimetype structure
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize an icaltimetype structure using the provided data
    struct icaltimetype dtstamp;
    dtstamp.year = (int16_t)((data[0] << 8) | data[1]);
    dtstamp.month = data[2] % 12 + 1; // Ensure valid month (1-12)
    dtstamp.day = data[3] % 31 + 1;   // Ensure valid day (1-31)
    dtstamp.hour = data[4] % 24;      // Ensure valid hour (0-23)
    dtstamp.minute = data[5] % 60;    // Ensure valid minute (0-59)
    dtstamp.second = data[6] % 60;    // Ensure valid second (0-59)
    dtstamp.is_date = data[7] % 2;    // Boolean value

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_dtstamp(dtstamp);

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

    LLVMFuzzerTestOneInput_46(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
