#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include "libical/ical.h"

extern "C" int LLVMFuzzerTestOneInput_362(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to fill an icalperiodtype structure
    if (size < sizeof(struct icalperiodtype)) {
        return 0;
    }

    // Initialize an icalperiodtype structure
    struct icalperiodtype period;

    // Fill the structure with data from the fuzzer
    // Assuming the icalperiodtype contains two time fields, start and end
    period.start.year = (int)(data[0] | (data[1] << 8));
    period.start.month = (int)(data[2] % 12 + 1); // Ensure valid month
    period.start.day = (int)(data[3] % 31 + 1);   // Ensure valid day
    period.start.hour = (int)(data[4] % 24);      // Ensure valid hour
    period.start.minute = (int)(data[5] % 60);    // Ensure valid minute
    period.start.second = (int)(data[6] % 60);    // Ensure valid second

    period.end.year = (int)(data[7] | (data[8] << 8));
    period.end.month = (int)(data[9] % 12 + 1);   // Ensure valid month
    period.end.day = (int)(data[10] % 31 + 1);    // Ensure valid day
    period.end.hour = (int)(data[11] % 24);       // Ensure valid hour
    period.end.minute = (int)(data[12] % 60);     // Ensure valid minute
    period.end.second = (int)(data[13] % 60);     // Ensure valid second

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_freebusy(period);

    // Cleanup
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

    LLVMFuzzerTestOneInput_362(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
