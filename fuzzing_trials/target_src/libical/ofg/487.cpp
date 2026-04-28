extern "C" {
    #include <libical/ical.h>
    #include <stdint.h>
    #include <stddef.h>
}

extern "C" int LLVMFuzzerTestOneInput_487(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract meaningful data for icaltimetype
    if (size < 9) { // Adjusted to 9 since we are using 9 bytes of data
        return 0;
    }

    // Initialize an icaltimetype structure from the input data
    struct icaltimetype tt;
    tt.year = (int)((data[0] << 8) | data[1]);
    tt.month = (int)(data[2] % 12 + 1);  // Ensure month is valid (1-12)
    tt.day = (int)(data[3] % 31 + 1);    // Ensure day is valid (1-31)
    tt.hour = (int)(data[4] % 24);       // Ensure hour is valid (0-23)
    tt.minute = (int)(data[5] % 60);     // Ensure minute is valid (0-59)
    tt.second = (int)(data[6] % 60);     // Ensure second is valid (0-59)
    tt.is_date = (int)(data[7] % 2);     // Boolean value
    // Removed tt.is_utc as it's not a member of icaltimetype
    tt.zone = NULL;                      // Set time zone to NULL for fuzzing

    // Call the function under test
    icalproperty *prop = icalproperty_new_tzuntil(tt);

    // Clean up the created property
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

    LLVMFuzzerTestOneInput_487(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
