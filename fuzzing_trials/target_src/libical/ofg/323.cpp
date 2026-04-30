#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_323(const uint8_t *data, size_t size) {
    // Initialize a struct icaldurationtype with some default values
    struct icaldurationtype duration;
    duration.is_neg = 0;
    duration.weeks = 0;
    duration.days = 0;
    duration.hours = 0;
    duration.minutes = 0;
    duration.seconds = 0;

    // Modify the struct fields based on the input data
    if (size >= 1) duration.is_neg = data[0] % 2;
    if (size >= 2) duration.weeks = data[1];
    if (size >= 3) duration.days = data[2];
    if (size >= 4) duration.hours = data[3];
    if (size >= 5) duration.minutes = data[4];
    if (size >= 6) duration.seconds = data[5];

    // Call the function-under-test
    char *ical_string = icaldurationtype_as_ical_string(duration);

    // Free the allocated string if it's not NULL
    if (ical_string != NULL) {
        free(ical_string);
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

    LLVMFuzzerTestOneInput_323(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
