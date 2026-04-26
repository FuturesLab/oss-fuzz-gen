#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_740(const uint8_t *data, size_t size) {
    // Ensure that the size is large enough to extract necessary fields
    if (size < sizeof(int) * 6) {
        return 0;
    }

    // Initialize the icaltimetype structure using data from the input
    struct icaltimetype tt;
    tt.year = ((int*)data)[0] % 3000;  // Limit to a reasonable year range
    tt.month = ((int*)data)[1] % 12 + 1;  // Month should be 1-12
    tt.day = ((int*)data)[2] % 31 + 1;  // Day should be 1-31
    tt.hour = ((int*)data)[3] % 24;  // Hour should be 0-23
    tt.minute = ((int*)data)[4] % 60;  // Minute should be 0-59
    tt.second = ((int*)data)[5] % 60;  // Second should be 0-59
    tt.is_date = 0;  // Assume it's a date-time
    tt.is_daylight = 0; // Not daylight saving time
    tt.zone = NULL;  // No specific time zone

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_dtend(tt);

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

    LLVMFuzzerTestOneInput_740(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
