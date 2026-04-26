#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include "libical/ical.h"

extern "C" int LLVMFuzzerTestOneInput_320(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract a valid ical_invalid_rrule_handling value
    if (size < sizeof(ical_invalid_rrule_handling)) {
        return 0;
    }

    // Extract a valid ical_invalid_rrule_handling value from the input data
    ical_invalid_rrule_handling handling = static_cast<ical_invalid_rrule_handling>(data[0] % 3); // Assuming there are 3 possible enum values

    // Call the function-under-test
    ical_set_invalid_rrule_handling_setting(handling);

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

    LLVMFuzzerTestOneInput_320(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
