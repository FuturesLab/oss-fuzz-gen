#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // Include for malloc and free

extern "C" {
    // Declare the function signature for icalrecur_string_to_freq
    typedef enum icalrecurrencetype_frequency {
        ICAL_NO_RECURRENCE = 0,
        ICAL_SECONDLY_RECURRENCE,
        ICAL_MINUTELY_RECURRENCE,
        ICAL_HOURLY_RECURRENCE,
        ICAL_DAILY_RECURRENCE,
        ICAL_WEEKLY_RECURRENCE,
        ICAL_MONTHLY_RECURRENCE,
        ICAL_YEARLY_RECURRENCE
    } icalrecurrencetype_frequency;

    // Assuming this function is defined in the C project
    icalrecurrencetype_frequency icalrecur_string_to_freq(const char *str);
}

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to safely convert to a C-style string
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Call the function-under-test
    icalrecurrencetype_frequency freq = icalrecur_string_to_freq(inputString);

    // Clean up
    free(inputString);

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

    LLVMFuzzerTestOneInput_50(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
