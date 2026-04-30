#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include necessary library for memcpy

extern "C" {
    // Declare the function from the C library
    typedef enum icalrecurrencetype_weekday {
        ICAL_RECURRENCE_WEEKDAY_NO,
        ICAL_RECURRENCE_WEEKDAY_SU,
        ICAL_RECURRENCE_WEEKDAY_MO,
        ICAL_RECURRENCE_WEEKDAY_TU,
        ICAL_RECURRENCE_WEEKDAY_WE,
        ICAL_RECURRENCE_WEEKDAY_TH,
        ICAL_RECURRENCE_WEEKDAY_FR,
        ICAL_RECURRENCE_WEEKDAY_SA
    } icalrecurrencetype_weekday;

    icalrecurrencetype_weekday icalrecur_string_to_weekday(const char *);
}

extern "C" int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated for safe string operations
    char *null_terminated_data = new char[size + 1];
    if (null_terminated_data == nullptr) {
        return 0; // If allocation fails, exit gracefully
    }

    // Copy the data to the new buffer and null-terminate it
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Call the function-under-test
    icalrecurrencetype_weekday result = icalrecur_string_to_weekday(null_terminated_data);

    // Clean up
    delete[] null_terminated_data;

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

    LLVMFuzzerTestOneInput_142(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
