#include <stdint.h>

// Wrap the necessary includes and code in extern "C"
extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for creating an icaltimetype
    if (size < 9) { // We need at least 9 bytes for the fields we are using
        return 0;
    }

    // Initialize an icaltimetype structure from the input data
    struct icaltimetype time;
    time.year = ((int16_t)data[0] << 8) | data[1];
    time.month = data[2] % 12 + 1; // Ensure month is between 1 and 12
    time.day = data[3] % 31 + 1;   // Ensure day is between 1 and 31
    time.hour = data[4] % 24;      // Ensure hour is between 0 and 23
    time.minute = data[5] % 60;    // Ensure minute is between 0 and 59
    time.second = data[6] % 60;    // Ensure second is between 0 and 59
    time.is_date = data[7] % 2;    // Boolean value
    // Removed the is_utc assignment as it doesn't exist in icaltimetype
    time.zone = NULL;              // Set zone to NULL

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_mindate(time);

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

    LLVMFuzzerTestOneInput_55(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
