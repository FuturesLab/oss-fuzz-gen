#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_342(const uint8_t *data, size_t size) {
    // Ensure the input size is reasonable to avoid excessive memory usage
    if (size == 0 || size > 1024) {
        return 0;
    }

    // Create an icalproperty object from the input data
    char *ical_data = (char *)malloc(size + 1);
    if (ical_data == NULL) {
        return 0;
    }
    memcpy(ical_data, data, size);
    ical_data[size] = '\0'; // Null-terminate the string

    // Parse the input data as an iCalendar property
    icalproperty *property = icalproperty_new_from_string(ical_data);
    free(ical_data);

    if (property == NULL) {
        return 0;
    }

    // Call the function-under-test
    struct icaltimetype dtend = icalproperty_get_dtend(property);

    // Clean up
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_342(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
