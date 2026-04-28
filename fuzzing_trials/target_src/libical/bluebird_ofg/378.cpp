#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include "libical/ical.h"
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_378(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *data_str = (char *)malloc(size + 1);
    if (data_str == NULL) {
        return 0;
    }
    memcpy(data_str, data, size);
    data_str[size] = '\0';  // Null-terminate the string

    // Create a dummy icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_DUE_PROPERTY);

    // Set a value to the property using the input data
    icalvalue *value = icalvalue_new_from_string(ICAL_DATETIME_VALUE, data_str);
    if (value != NULL) {
        icalproperty_set_value(prop, value);

        // Call the function-under-test
        struct icaltimetype due = icalproperty_get_due(prop);

        // Use the result to avoid any compiler optimizations that might skip the call
        if (due.is_date) {
            // Do something trivial with the result
            due.year += 1;
        }

        // Clean up
        icalvalue_free(value);
    }

    // Free the icalproperty object
    icalproperty_free(prop);
    free(data_str);

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

    LLVMFuzzerTestOneInput_378(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
